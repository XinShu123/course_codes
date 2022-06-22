#include "virtual_memory.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>


__device__  int count=0;

__device__ void init_invert_page_table(VirtualMemory *vm) {

  for (int i = 0; i < vm->PAGE_ENTRIES; i++) {
    vm->invert_page_table[i] = 0x80000000; // invalid := MSB is 1
    vm->invert_page_table[i + vm->PAGE_ENTRIES] = -1; //corresponding virtual address
    vm->invert_page_table[i + 2* vm->PAGE_ENTRIES] = 0;//count number
  }
}

__device__ void vm_init(VirtualMemory *vm, uchar *buffer, uchar *storage,
                        u32 *invert_page_table, int *pagefault_num_ptr,
                        int PAGESIZE, int INVERT_PAGE_TABLE_SIZE,
                        int PHYSICAL_MEM_SIZE, int STORAGE_SIZE,
                        int PAGE_ENTRIES) {
  // init variables
  vm->buffer = buffer;
  vm->storage = storage;
  vm->invert_page_table = invert_page_table;
  vm->pagefault_num_ptr = pagefault_num_ptr;

  // init constants
  vm->PAGESIZE = PAGESIZE;
  vm->INVERT_PAGE_TABLE_SIZE = INVERT_PAGE_TABLE_SIZE;
  vm->PHYSICAL_MEM_SIZE = PHYSICAL_MEM_SIZE;
  vm->STORAGE_SIZE = STORAGE_SIZE;
  vm->PAGE_ENTRIES = PAGE_ENTRIES;

  // before first vm_write or vm_read
  init_invert_page_table(vm);
}

__device__ uchar vm_read(VirtualMemory *vm, u32 addr) {
    int offset = addr % 32; //capture last 5 digits
    uchar result;
    bool find = false;
    for (int i = 0; i < vm->PAGE_ENTRIES; i++)
    {
        

        if (vm->invert_page_table[i + vm->PAGE_ENTRIES] == addr>>5 && vm->invert_page_table[i]==0) //2^10 -> 2^12
        {
            //printf("read successful, virtual address is %d!\n", vm->invert_page_table[i + vm->PAGE_ENTRIES]);
            result = vm->buffer[i*32 + offset];//2^15
            count++;
            vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES]=count;//count plus
            find = true;
            break;
        }
    }
    if (!find)
    {
        (*vm->pagefault_num_ptr)++; //increase page fault number
        //printf("preform read LRU\n");
        int comp_count = 999999999999;
        int smallest = 0;
        for (int i = 0; i < vm->PAGE_ENTRIES; i++)
        {
            if (vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] < comp_count)
            {
                comp_count = vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES];
                smallest = i;
            }
        }
        int virtual_page_number = vm->invert_page_table[smallest + vm->PAGE_ENTRIES];//2^12
        for (int j = 0; j < vm->PAGESIZE; j++)
        {
            int offset = j;
            u32 physical_address = smallest * 32 + offset;
            u32 virtual_address = virtual_page_number * 32 + offset;
            vm->storage[virtual_address] = vm->buffer[physical_address]; //swap out to storage
        }
        vm->invert_page_table[smallest + vm->PAGE_ENTRIES] = addr >> 5; //update invert page table
        count++;
        vm->invert_page_table[smallest + 2 * vm->PAGE_ENTRIES] = count; //update count
        for (int j = 0; j < vm->PAGESIZE; j++)
        {
            int offset = j;
            int virtual_page_number = addr>>5;
            u32 virtual_address = virtual_page_number * 32 + offset;
            u32 physical_address = smallest * 32 + offset;
            vm->buffer[physical_address] = vm->storage[virtual_address]; //swap the desired page in physical memory
        }
        //printf("virtual page %d is replaced by new virtual page %d", virtual_page_number, addr >> 5);
        result = vm->buffer[smallest * 32 + offset];

    }



  /* Complete vm_read function to read single element from data buffer */
  return result; //TODO
}

__device__ void vm_write(VirtualMemory *vm, u32 addr, uchar value) {
  /* Complete vm_write function to write value into data buffer */
    
    
    int virtual_page_number = addr >> 5;
    int offset = addr % 32;
    //printf("vpn = %d, offset = %d\n", virtual_page_number, offset);
    bool find=false;

    for (int i = 0; i < vm->PAGE_ENTRIES; i++)
    {
        if (vm->invert_page_table[i + vm->PAGE_ENTRIES] == virtual_page_number)
        {
            find = true; //if find
            u32 physical_address = i * 32 + offset;
            //printf("physical addr: %d\n", physical_address);
            //vm->invert_page_table[i] = 0; //set to not empty
            //vm->invert_page_table[i + vm->PAGE_ENTRIES] = virtual_page_number;
            vm->buffer[physical_address] = value; //write in physical memory
            count++;//more recently written page will have bigger count, so count is static int variable
            vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] = count;//update count
            break; //once find, then stop
        }
        
    }
    if (!find)
    {
        (*vm->pagefault_num_ptr)++;
        //printf("This page faault number = %d\n", *(vm->pagefault_num_ptr));
        for (int i = 0; i < vm->PAGE_ENTRIES; i++)
        {
            if (vm->invert_page_table[i] == 0x80000000)
            {
                find = true; //if find
                u32 physical_address = i << 5 + offset;
                vm->invert_page_table[i] = 0; //set to not empty
                vm->invert_page_table[i + vm->PAGE_ENTRIES] = virtual_page_number;
                //printf("bind virtual page number %d to physiacal frame number %d\n", virtual_page_number, i);
                vm->buffer[physical_address] = value; //write in physical memory
                count++;//more recently written page will have bigger count, so count is static int variable
                vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] = count;//update count
                break; //once find, then stop

            }

        }
    }
    if(!find)
    {
        //if there is no physical page for this logical page, and there is no empty page, there is need to swap
        // (*vm->pagefault_num_ptr)++;
        //printf("perform LRU\n");
        // printf("This page faault number = %d\n", *(vm->pagefault_num_ptr));
        int comp_count = 999999999999;
        int smallest = 0;
        for (int i = 0; i < vm->PAGE_ENTRIES; i++)
        {
            if (vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] < comp_count)
            {
                comp_count = vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES];
                smallest = i;
            }
        }
        //printf("smallest virtual page number %d replaced by new %d\n", smallest, virtual_page_number);




        for (int j = 0; j < vm->PAGESIZE; j++)
        {
            int offset_local = j;
            u32 physical_address = smallest * 32 + offset_local;
            u32 virtual_address = vm->invert_page_table[smallest + vm->PAGE_ENTRIES] * 32 + offset_local;
            vm->storage[virtual_address] = vm->buffer[physical_address]; //swap out to storage
        }


        vm->invert_page_table[smallest + vm->PAGE_ENTRIES] = virtual_page_number; //update invert page table
        count++;
        vm->invert_page_table[smallest + 2 * vm->PAGE_ENTRIES] = count; //update count
        u32 physical_address = smallest * 32 + offset;
        vm->buffer[physical_address] = value;
    }


    
    
   
    /*if (offset == 0)
    {
        bool find = false;
        for (int i = 0; i < vm->PAGE_ENTRIES; i++)
        {
            if (vm->invert_page_table[i] == 0x80000000)
            {
                find = true; //if find
                u32 physical_address = i << 5 + offset;
                vm->invert_page_table[i] = 0; //set to not empty
                vm->invert_page_table[i + vm->PAGE_ENTRIES] = virtual_page_number;
                vm->buffer[physical_address] = value; //write in physical memory
                count++;//more recently written page will have bigger count, so count is static int variable
                vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] = count;//update count
                break; //once find, then stop

            }
        }
        if (!find)
        {
            (*vm->pagefault_num_ptr)++;
            int comp_count = 999999999999;
            int smallest = 0;
            for (int i = 0; i < vm->PAGE_ENTRIES; i++)
            {
                if (vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] < comp_count)
                {
                    comp_count = vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES];
                    smallest = i;
                }
            }
            


            
           
            for (int j = 0; j < vm->PAGESIZE; j++)
            {
                int offset = j;
                u32 physical_address = smallest << 5 + offset;
                u32 virtual_address = vm->invert_page_table[smallest + vm->PAGE_ENTRIES] << 5 + offset;
                vm->storage[virtual_address] = vm->buffer[physical_address]; //swap out to storage
            }
            

            vm->invert_page_table[smallest + vm->PAGE_ENTRIES] = virtual_page_number; //update invert page table
            count++;
            vm->invert_page_table[smallest + 2 * vm->PAGE_ENTRIES] = count; //update count
            u32 physical_address = smallest << 5 + offset;
            vm->buffer[physical_address] = value;

        }


    }
    else
    {
        bool find=false;
        for (int i = 0; i < vm->PAGE_ENTRIES; i++)
        {
            if (vm->invert_page_table[i + vm->PAGE_ENTRIES] == virtual_page_number)
            {
                find=true;
                u32 physical_address = i << 5 + offset;
                vm->buffer[physical_address] = value;
                count++;
                vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] = count;

                break;
            }
        }
        if (!find)
        {
            (*vm->pagefault_num_ptr)++;
            int comp_count = 999999999999;
            int smallest = 0;
            for (int i = 0; i < vm->PAGE_ENTRIES; i++)
            {
                if (vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES] < comp_count)
                {
                    comp_count = vm->invert_page_table[i + 2 * vm->PAGE_ENTRIES];
                    smallest = i;
                }
            }
            for (int j = 0; j < vm->PAGESIZE; j++)
            {
                int offset = j;
                u32 physical_address = smallest << 5 + offset;
                u32 virtual_address = vm->invert_page_table[smallest + vm->PAGE_ENTRIES] << 5 + offset;
                vm->storage[virtual_address] = vm->buffer[physical_address]; //swap out to storage
            }


            vm->invert_page_table[smallest + vm->PAGE_ENTRIES] = virtual_page_number; //update invert page table
            count++;
            vm->invert_page_table[smallest + 2 * vm->PAGE_ENTRIES] = count; //update count
            u32 physical_address = smallest << 5 + offset;
            vm->buffer[physical_address] = value;

        }
    }*/
}

__device__ void vm_snapshot(VirtualMemory* vm, uchar* results, int offset,
    int input_size)

{
    uchar result;
    for (int i = 0; i < input_size; ++i) {
        result = vm_read(vm, i);
        results[i] = result;
    }
    
}
   

  /* Complete snapshot function togther with vm_read to load elements from data
   * to result buffer */


