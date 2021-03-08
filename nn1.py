import numpy as np
import datasplit
import datetime
class FullyConnectedLayer(object):
    def __init__(self,input_size,output_size,activator):
        self.input_size=input_size
        self.output_size=output_size
        self.activator=activator()
        #self.W=np.random.uniform(0,1,(output_size,input_size))
        self.W = np.random.randn(output_size, input_size)
        self.b=np.zeros((output_size,1))
        self.output=np.zeros((output_size,1))
    def forward(self,input_array):
        self.input=input_array.reshape(input_array.shape[0],1)
        temp=np.dot(self.W,input_array)
        self.output=self.activator.forward(temp.reshape(temp.shape[0],1)+self.b)

    def backward(self,delta_array,lemta):
        #print(delta_array)
        self.delta=self.activator.backward(self.input)*np.dot(self.W.T,delta_array)
        self.W_grad=np.dot(delta_array,self.input.T)+lemta*self.W
        #print(self.W_grad)
        self.b_grad=delta_array
        #print(self.b_grad)
    def update(self,learn_rate):
        self.W-=learn_rate*self.W_grad
        self.b-=learn_rate*self.b_grad
class SigmoidActivator(object):
    def forward(self,weighted_input):
        return 1.0/(1.0+np.exp(-weighted_input))
    def backward(self,output):
        return output*(1-output)

class TanhActivator(object):
    def forward(self,input1):

        return np.tanh(input1)
    def backward(self,output):
        return (1-output**2)
class Network(object):
    def __init__(self):
        self.layers=[]
        self.layers.append(FullyConnectedLayer(3072,64,TanhActivator))
        self.layers.append(FullyConnectedLayer(64,15,SigmoidActivator))
    def predict(self,sample):
        output=sample
        for layer in self.layers:
            layer.forward(output)
            output=layer.output
        return output
    def train(self,labels,data_set,learn_rate,lemta):

        for d in range(len(data_set)):
            self.train_one_sample(labels[d],data_set[d],learn_rate,lemta)
    def train_one_sample(self,label,sample,learn_rate,lemta):
        self.predict(sample)
        self.calc_gradient(label,lemta)
        self.update_weight(learn_rate)
    def calc_gradient(self,label,lemta):
        label1=label.reshape(label.shape[0],1)
        delta=self.layers[-1].activator.backward(self.layers[-1].output)*(label1-self.layers[-1].output)

        for layer in self.layers[::-1]:
            layer.backward(delta,lemta)
            delta=layer.delta
        return delta
    def update_weight(self,learn_rate):
        for layer in self.layers:
            layer.update(learn_rate)
def get_result(vec):
    max_value_index=0
    max_value=0
    for i in range(len(vec)):
        if vec[i]>max_value:
            max_value=vec[i]
            max_value_index=i
    return max_value_index
def evaluate(Network, test_data_set,test_labels):
    error=0
    total=len(test_data_set)
    for i in range(total):
        label=get_result(test_labels[i])
        predict=get_result(Network.predict(test_data_set[i]))
        if label!=predict:
            error+=1
        return 1-float(error)/float(total)
def train_and_evalute():
    last_error_ratio=1.0
    epoch=0
    train_data_set,train_labels=datasplit.get_training_data_set()
    test_data_set,test_labels=datasplit.get_test_data_set()
    network=Network()
    learn_rate=0.01
    lemta=np.exp(-18)
    while True:
        epoch+=1
        network.train(train_labels,train_data_set,learn_rate,lemta)
        print ('%s epoch %d finished' % (datetime.datetime.now(),epoch))
        if epoch % 10 == 0:
            error_ratio=evaluate(network,test_data_set,test_labels)
            print('%s after epoch %d, accuracy ratio is %f' % (datetime.datetime.now(),epoch,error_ratio))
            if error_ratio>last_error_ratio:
                break
            else:
                last_error_ratio=error_ratio
if __name__=="__main__":
    train_and_evalute()




