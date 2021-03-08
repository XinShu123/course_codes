import os
import random
import numpy as np
import resize_final


def number_gen(train_per_sub = 4):
    sample = []
    for i in range(15):
        rad = random.sample(range(1,12),train_per_sub)
        mod_rad = [x+i*11 for x in rad]
        sample = sample + mod_rad
    
    return sample
    

def split(train = 4):
    ## we have 15 subjects in total, every subject has 11 images for different angles. The only parameter needed is train_per_sub.
    ## return training set and testing set, with two different labeling scheme for output
    ## one is [1...15], another is one hot encoding [1,0,0,0,0,0,...]
    ## pick the one you need to use, and check the dimension.
    ## please look at the specification of the dataset that is returned in this function.
    dir_path = os.path.dirname(__file__)
    filename = dir_path + "/yaleface_adjusted/"
    A = resize_final.final_matrix(filename,64,48)

    train_list = number_gen(train)
    train_list = [x-1 for x in train_list]
    X_train = A[train_list,:]
    a = range(1,16)
    b = range(train)
    y_train = [val for val in a for _ in b]
    y_train = np.matrix(y_train)
    y_train = np.transpose(y_train)
    y_train_hot = np.zeros((y_train.shape[0],15))
    for i in range(y_train.shape[0]):
        y_train_hot[i,y_train[i]-1] = 1

    
    X_test = np.delete(A,train_list,0)
    b = range(11-train)
    y_test = [val for val in a for _ in b]
    y_test = np.matrix(y_test)
    y_test = np.transpose(y_test)
    y_test_hot = np.zeros((y_test.shape[0],15))
    for i in range(y_test.shape[0]):
        y_test_hot[i,y_test[i]-1] = 1

    dataset = {
        "x_train": X_train,
        "y_train": y_train,
        "y_train_he": y_train_hot,
        "x_test": X_test,
        "y_test": y_test,
        "y_test_he": y_test_hot
    }

    return dataset

def get_training_data_set():
    a=split(10)
    return a["x_train"],a["y_train_he"]
def get_test_data_set():
    a=split(10)
    return a["x_test"],a["y_test_he"]


if __name__ == "__main__":
    dataset = split(8)
    print(dataset["x_train"].shape)
    print("###################")
    #print(dataset["y_train"])
    #print("###################")
    print(dataset["y_train_he"].shape)
    print("###################")
    print(dataset["x_test"].shape)
    #print("###################")
    #print(dataset["y_test"])
    print("###################")
    print(dataset["y_test_he"].shape)
    #print("###################")