#include "file_system.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


__device__ __managed__ u16 modify_time = 0;
__device__ __managed__ u16 create_time = 0;

__device__ __managed__ u16 most_adv_0_block = 0; //indicate the first available block
__device__ __managed__ u16 most_adv_0_fcb = 0; //indicate the first fcb which is not used





__device__ void fs_init(FileSystem *fs, uchar *volume, int SUPERBLOCK_SIZE,
							int FCB_SIZE, int FCB_ENTRIES, int VOLUME_SIZE,
							int STORAGE_BLOCK_SIZE, int MAX_FILENAME_SIZE, 
							int MAX_FILE_NUM, int MAX_FILE_SIZE, int FILE_BASE_ADDRESS)
{
  // init variables
  fs->volume = volume;
  

  // init constants
  fs->SUPERBLOCK_SIZE = SUPERBLOCK_SIZE;
  fs->FCB_SIZE = FCB_SIZE;
  fs->FCB_ENTRIES = FCB_ENTRIES;
  fs->STORAGE_SIZE = VOLUME_SIZE;
  fs->STORAGE_BLOCK_SIZE = STORAGE_BLOCK_SIZE;
  fs->MAX_FILENAME_SIZE = MAX_FILENAME_SIZE;
  fs->MAX_FILE_NUM = MAX_FILE_NUM;
  fs->MAX_FILE_SIZE = MAX_FILE_SIZE;
  fs->FILE_BASE_ADDRESS = FILE_BASE_ADDRESS;

}





__device__ u32 fs_open(FileSystem *fs, char *s, int op)
{
	/* Implement open operation here */
	u32 location = 0;
	
	
	
	//printf("most_adv_0_block: %d; most_adv_0_fcb: %d\n", most_adv_0_block, most_adv_0_fcb);
	bool find = false; //indicate whether file name is found or not
	int i;
	for (i = 0; i < 1024; i++) {
		for (int j = 0; j < 20; j++) {
			if (fs->volume[4096 + i * 32 + j] == s[j]) {
				if (s[j] == '\0') {
					find = true;
					break;
				}
			}
			else break;
		}
		if (find) {
			break;
		}
		
	}
	///printf("find: %d\n",find);
	///printf("i: %d\n", i);
	if (find) {
		if (op == G_READ) {
			
			fs->volume[4096 + i * 32 + 20] = G_READ; //update mode
			location = fs->volume[4096 + i * 32 + 21] * 256 + fs->volume[4096 + i * 32 + 22]; //return location
		}
		else if (op == G_WRITE) {
			u16 ctime = fs->volume[4096 + i * 32 + 27] * 256 + fs->volume[4096 + i * 32 + 28];
			u16 size = fs->volume[4096 + i * 32 + 23] * 256 + fs->volume[4096 + i * 32 + 24];
			///printf("ttqqsize/256: %d; size!256: %d\n", fs->volume[4096 + i * 32 + 23], fs->volume[4096 + i * 32 + 24]);
			u16 block_offset = 0;
			if (size % 32 > 0) {
				block_offset = size / 32 + 1;
			}
			else if (size % 32 == 0) {
				block_offset = size / 32;
			}
			//u16 location_local = fs->volume[4096 + i * 32 + 21] * 256 + fs->volume[4096 + i * 32 + 22];
			// compact FCB
			/*for (int j = 4096 + (i + 1) * 32; j <= 4096 + ( most_adv_0_fcb - 2 )* 32; j += 32) {
				for (int k = 0; k < 32; k++) {
					fs->volume[j - 32 + k] = fs->volume[j + k];
				}

			}*/
			for (int j = 4096 + (i + 1) * 32; j < 4096 + most_adv_0_fcb * 32; j ++) {
				
					fs->volume[j - 32] = fs->volume[j];
				

			}
			most_adv_0_fcb--;
			//compact the volume
			u16 original_location = fs->volume[4096 + i * 32 + 21] * 256 + fs->volume[4096 + i * 32 + 22];
			//printf("original_location: %d\n", original_location);
			//u16 new_location = original_location - block_offset;
			/*for (int m = 36864 + (original_location - 1) * 32; m <= 36864 + (most_adv_0_block - 2) * 32; m += 32) {
				for (int n = 0; n < block_offset * 32; n++) {
					fs->volume[36864 + new_location + n] = fs->volume[36864 + original_location + n];
				}
			}*/
			for (int m = 36864 + original_location * 32; m < 36864 + most_adv_0_block * 32; m ++) {
				
					fs->volume[m-block_offset*32] = fs->volume[m];
				
			}
			most_adv_0_block -= block_offset;
			int l = i;
			// update location in FCB 
			for (l = 4096+i*32; l <= 4096 + (most_adv_0_fcb - 1) * 32; l += 32) {
				u16 new_location = fs->volume[l+ 21] * 256 + fs->volume[l + 22]-block_offset;
				fs->volume[l+ 21] = new_location / 256;
				fs->volume[l+ 22] = new_location % 256;
				//printf("location/256: %d; location!256: %d\n", fs->volume[4096 + l * 32 + 21], fs->volume[4096 + l * 32 + 22]);

			}
			location = most_adv_0_block;
			
			//create FCB for this file
			for (int o = 0; o < 20; o++) {
				fs->volume[4096 + most_adv_0_fcb * 32 + o] = s[o];
			}
			fs->volume[4096 + most_adv_0_fcb * 32 + 20] = G_WRITE;
			fs->volume[4096 + most_adv_0_fcb * 32 + 21] = location / 256;
			fs->volume[4096 + most_adv_0_fcb * 32 + 22] = location % 256;
			fs->volume[4096 + most_adv_0_fcb * 32 + 23] = 0; 
			fs->volume[4096 + most_adv_0_fcb * 32 + 24] = 0;
			fs->volume[4096 + most_adv_0_fcb * 32 + 27] = ctime / 256;
			fs->volume[4096 + most_adv_0_fcb * 32 + 28] = ctime % 256;
			fs->volume[4096 + most_adv_0_fcb * 32 + 29] = UNUSED;
            //update most_adv_0_fcb
			most_adv_0_fcb++;

			


		}
		 
	}

	
	else if (op == G_WRITE) {
		create_time++;
		location = most_adv_0_block;

		//create FCB for this file
		for (int o = 0; o < 20; o++) {
			fs->volume[4096 + most_adv_0_fcb * 32 + o] = s[o];
		}
		fs->volume[4096 + most_adv_0_fcb * 32 + 20] = G_WRITE;
		fs->volume[4096 + most_adv_0_fcb * 32 + 21] = location / 256;
		fs->volume[4096 + most_adv_0_fcb * 32 + 22] = location % 256;
		//printf("location/256: %d; location!256: %d\n", location / 256, location % 256);
		fs->volume[4096 + most_adv_0_fcb * 32 + 23] = 0;
		fs->volume[4096 + most_adv_0_fcb * 32 + 24] = 0;
		fs->volume[4096 + most_adv_0_fcb * 32 + 27] = create_time / 256;
		fs->volume[4096 + most_adv_0_fcb * 32 + 28] = create_time % 256;
		fs->volume[4096 + most_adv_0_fcb * 32 + 29] == UNUSED;
	/*for (int o = 0; o < 20; o++) {
			printf("%c", s[o]);
		}
		printf("create_time: %d\n", create_time);*/
		//update most_adv_0_fcb
		most_adv_0_fcb++;


	}
	return location;
	



}


__device__ void fs_read(FileSystem *fs, uchar *output, u32 size, u32 fp)
{
	/* Implement read operation here */
	assert(size <= 1024);

	
	
	for (int g = 0; g < size; g++) {
		output[g] = fs->volume[36864 + fp * 32 + g];
	}
	
	
}

__device__ u32 fs_write(FileSystem *fs, uchar* input, u32 size, u32 fp)
{
	/* Implement write operation here */
	assert(size <= 1024);
	u16 block_offset = 0;
	if (size % 32 > 0) {

		block_offset = size / 32 + 1;
	}
	else if (size % 32 == 0) {
		block_offset = size / 32;
	}
	if (fs->volume[4096 + (most_adv_0_fcb-1) * 32 + 20] == G_WRITE) {
		//write in storage
		for (int h = 0; h < size; h++) {
			fs->volume[36864 + fp * 32 + h] = input[h];
		}
		//update most_adv_0_block
		most_adv_0_block += block_offset;
		//update modify_time
		modify_time++;
		//update FCB
		fs->volume[4096 + (most_adv_0_fcb - 1) * 32 + 25] = modify_time / 256;
		fs->volume[4096 + (most_adv_0_fcb - 1) * 32 + 26] = modify_time % 256;
		fs->volume[4096 + (most_adv_0_fcb - 1) * 32 + 23] = size / 256;
		fs->volume[4096 + (most_adv_0_fcb - 1) * 32 + 24] = size % 256;
		///printf("size/256: %d; size!256: %d\n", size / 256, size % 256);

	}
	else {
		printf("Wrong operation. Not permitted!\n");
	}
	return fp;

}
__device__ void fs_gsys(FileSystem *fs, int op)
{
	/* Implement LS_D and LS_S operation here */
	
	if (op == LS_D) {
		printf("===sort by modified time===\n");
		u16 largest_mtime = 0;
		int largest = -1;
		int r = 0;
		while (r <= most_adv_0_fcb-1) {
			for (int f = 0; f <= (most_adv_0_fcb - 1); f++) {
				u16 mtime = fs->volume[4096 + f * 32 + 25] * 256 + fs->volume[4096 + f * 32 + 26];
				if (mtime > largest_mtime && fs->volume[4096 + f * 32 + 29]==UNUSED) {
					largest = f;
					largest_mtime = mtime;
					
					
				}
			
			}
			fs->volume[4096 + largest * 32 + 29] = USED;
			/*for (int d = 0; d < 20; d++) {
				printf("%c", fs->volume[4096 + largest * 32 + d]);
			}*/
			printf("%s", &fs->volume[4096 + largest * 32]);
			printf("\n");
			largest_mtime = 0;

			r++;
		}
		for (int f = 0; f <= (most_adv_0_fcb - 1); f++) {
			fs->volume[4096 + f * 32 + 29] = UNUSED;
		} 
	}
	else if (op == LS_S) {
		printf("===sort by size===\n");
		u16 largest_size = 0;
		u16 ctime_of_largest = 0;
		int largest = -1;
		int r = 0;
		while (r <= most_adv_0_fcb - 1) {
			for (int f = 0; f <= (most_adv_0_fcb - 1); f++) {
				//u16 ctime = fs->volume[4096 + f * 32 + 27] * 256 + fs->volume[4096 + f * 32 + 28];
				//u16 ctime_of_largest = fs->volume[4096 + largest * 32 + 27] * 256 + fs->volume[4096 + largest * 32 + 28];
				u16 size = fs->volume[4096 + f * 32 + 23] * 256 + fs->volume[4096 + f * 32 + 24];
				//printf("size is %d\n", size);
				//since files that create later will definitely locate behind files create before
				//condition: ((size > largest_size) || ((size == largest_size) && (ctime < ctime_of_largest)))
				if (fs->volume[4096 + f * 32 + 29] == UNUSED) {
					if (size > largest_size) {
						largest = f;
						largest_size = size;
						ctime_of_largest = fs->volume[4096 + f * 32 + 27] * 256 + fs->volume[4096 + f * 32 + 28];
					}
					else if (size == largest_size) {
					    u16 ctime = fs->volume[4096 + f * 32 + 27] * 256 + fs->volume[4096 + f * 32 + 28];
						if (ctime < ctime_of_largest) {
							largest = f;
							largest_size = size;
							ctime_of_largest = ctime;
						}
					}
					

				}
				
				
			
			}
			//printf("largest is %dth file.\n", largest);
			fs->volume[4096 + largest * 32 + 29] = USED;
			/*for (int d = 0; d < 20; d++) {
				printf("%c", fs->volume[4096 + largest * 32 + d]);
			}*/
			printf("%s", &fs->volume[4096 + largest * 32]);
			printf("  %d\n", largest_size);
			largest_size = 0;
			ctime_of_largest = 0;
			r++;
		}

		for (int f = 0; f <= (most_adv_0_fcb - 1); f++) {
			fs->volume[4096 + f * 32 + 29] = UNUSED;
		}

	}

}

__device__ void fs_gsys(FileSystem *fs, int op, char *s)
{
	/* Implement rm operation here */
	
	if (op == RM) {
		
		bool find = false; 
		int i;
		for (i = 0; i < 1024; i++) {
			for (int j = 0; j < 20; j++) {
				if (fs->volume[4096 + i * 32 + j] == s[j]) {
					if (s[j] == '\0') {
						find = true;
						break;
					}
				}
				else break;
			}
			if (find) {
				break;
			}

		}
		if (!find) {
			printf("file not found! invalid operation.\n");
		}
		else {
			u16 size = fs->volume[4096 + i * 32 + 23] * 256 + fs->volume[4096 + i * 32 + 24];
			u16 block_offset = 0;
			if (size % 32 > 0) {
				block_offset = size / 32+1;
			}
			else if (size % 32 == 0) {
				block_offset = size / 32;
			}
			
			//u16 location_local = fs->volume[4096 + i * 32 + 21] * 256 + fs->volume[4096 + i * 32 + 22];
			// compact FCB
			for (int j = 4096 + (i + 1) * 32; j < 4096 + most_adv_0_fcb * 32; j++) {

				fs->volume[j - 32] = fs->volume[j];


			}
			most_adv_0_fcb--;
			//compact the volume
			u16 original_location = fs->volume[4096 + i * 32 + 21] * 256 + fs->volume[4096 + i * 32 + 22];
			for (int m = 36864 + original_location * 32; m < 36864 + most_adv_0_block * 32; m++) {

				fs->volume[m - block_offset * 32] = fs->volume[m];

			}
			most_adv_0_block -= block_offset;
			// update location in FCB
			int l = i;
			for (l = 4096+i*32; l <= 4096 + (most_adv_0_fcb - 1) * 32; l += 32) {
				u16 new_location = fs->volume[l+21] * 256 + fs->volume[l+22] - block_offset;
				fs->volume[l + 21] = new_location / 256;
				fs->volume[l + 22] = new_location % 256;
			}
			
			


		}

	}
	else {
		printf("permission denied!\n");
	}
}

__device__ void printfcb(FileSystem * fs) {
	
	for (int i = 0; i < most_adv_0_fcb; i++) {
		
		printf("the %dth file: ", i);
		/*for (int j = 0; j < 20; j++) {
			if (fs->volume[4096 + i * 32 + j] == '\0') break;
			printf("%c", fs->volume[4096 + i * 32 + j]);
		}*/
		
			
	    printf("%s", &fs->volume[4096 + i * 32]);
		
		printf(" size: %d", fs->volume[4096 + i * 32 + 23] * 256 + fs->volume[4096 + i * 32 + 24]);
		printf("\n");
	}
}
























































































































			
