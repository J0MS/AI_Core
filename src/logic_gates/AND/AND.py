import torch
from torch.autograd import Variable
import torch.nn as nn
#import torch.nn.functional #as F
import torch.optim as optim

EPOCHS_TO_TRAIN = 50000

#Class definition, subclass of nn.Module
class Net(nn.Module):

    def __init__(self):
        super(Net, self).__init__()
        self.fc1 = nn.Linear(2, 3, True) # 2 Input channels, 3 Output channels, bias = True
        self.fc2 = nn.Linear(3, 1, True) # 3 Input channels, 1 Output channels, bias = True

    # Method for generate the net output
    def forward(self, x):
        x = torch.sigmoid(self.fc1(x))
        x = self.fc2(x)
        return x

# Create a object of Net class
net = Net()

# Create a Tensor for inputs
inputs = list(map(lambda s: Variable(torch.Tensor([s])), [
    [0, 0],
    [0, 1],
    [1, 0],
    [1, 1]
]))

# Create a Tensor for targets
targets = list(map(lambda s: Variable(torch.Tensor([s])), [
    [0],
    [0],
    [0],
    [1]
]))

#Loss function
criterion = nn.MSELoss()

#Optimizer, using Sthochastic gradient descent, takes as arguments parameters of network and learning rate.
optimizer = optim.SGD(net.parameters(), lr=0.01)

#print("Parametros",list(net.parameters()) )

print("Training cycle:")
for idx in range(0, EPOCHS_TO_TRAIN):
    for input, target in zip(inputs, targets):
        optimizer.zero_grad()   # zeroes the gradient buffers
        output = net(input) # Get net output buffer
        loss = criterion(output, target) # Get errors
        loss.backward() #Backpropagation
        optimizer.step()    # Update weigths
    if idx % 5000 == 0:
        print("Epoch {: >8} Loss: {}".format(idx, loss.data.numpy() )  )



print("")
print("Final results:")
for input, target in zip(inputs, targets):
    output = net(input)
    print("Input:[{},{}] Target:[{}] Predicted:[{}] Error:[{}]".format(
        int(input.data.numpy()[0][0]),
        int(input.data.numpy()[0][1]),
        int(target.data.numpy()[0]),
        round(float(output.data.numpy()[0]), 4),
        round(float(abs(target.data.numpy()[0] - output.data.numpy()[0])), 4)
    ))
