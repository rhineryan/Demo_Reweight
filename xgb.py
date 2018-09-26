from __future__ import division, print_function, absolute_import

import matplotlib
matplotlib.use('Agg')

import xgboost as xgb
from xgboost import plot_importance
from xgboost import plot_tree
from graphviz import Digraph
import numpy as np
import matplotlib.pyplot as plt
from sklearn import metrics

data=np.loadtxt("P_kal.dat")
'''print(data.shape)'''
#shuffled_dataset
permutation = np.random.permutation(data.shape[0])
sdata = data[permutation]

#train and test data
sz = sdata.shape

train = sdata[:int(sz[0] * 0.6), :]
test = sdata[int(sz[0] * 0.6):int(sz[0] * 0.8), :]
val = sdata[int(sz[0] * 0.8):, :]

train_X = train[:, 1:29]
train_Y = train[:, 29]

test_X = test[:, 1:29]
test_Y = test[:, 29]

val_X = val[:, 1:29]
val_Y = val[:, 29]


print(val.shape,val_Y[1:10])
print(test.shape,test_Y[1:10])
print(train.shape,train_Y[1:10])


xg_train = xgb.DMatrix(train_X, label=train_Y)
xg_test = xgb.DMatrix(test_X, label=test_Y)
xg_val = xgb.DMatrix(val_X, label=val_Y)
# setup parameters for xgboost
param = {}
# use softmax multi-class classification
param['objective'] = 'multi:softmax'
# scale weight of positive examples
param['eta'] = 0.1
param['max_depth'] = 6
param['silent'] = 1
param['nthread'] = 4
param['num_class'] = 2

watchlist = [(xg_train, 'train'), (xg_test, 'test')]

num_round = 200
'''
bst = xgb.train(param, xg_train, num_round, watchlist)
##plot
plot_importance(bst)
#plot_tree(bst)
plt.savefig("importance.png")
# get prediction
pred = bst.predict(xg_test)
error_rate = np.sum(pred != test_Y) / test_Y.shape[0]
predv = bst.predict(xg_val)
error_ratev = np.sum(predv != val_Y) / val_Y.shape[0]
print('Test error using softmax = {}'.format(error_rate))
print('Val error:',error_ratev)
'''


# do the same thing again, but output probabilities
param['objective'] = 'multi:softprob'
bst = xgb.train(param, xg_train, num_round, watchlist)
# Note: this convention has been changed since xgboost-unity
# get prediction, this is in 1D array, need reshape to (ndata, nclass)
pred_prob = bst.predict(xg_test).reshape(test_Y.shape[0], 2)
pred_label = np.argmax(pred_prob, axis=1)
error_rate = np.sum(pred_label != test_Y) / test_Y.shape[0]
print('Test error using softprob = {}'.format(error_rate))

#----------------------------------------
f=open("xgb_predict.txt","wb")
f1=open("xgb_input.txt","wb")
pr=np.array(bst.predict(xg_val).reshape(val_Y.shape[0], 2)[:,1])
np.savetxt(f,pr)
np.savetxt(f,val_Y)
np.savetxt(f1,val_X[:,0:2])

#---------------------------------------

###-----------------------------------------
fpr, tpr, thresholds = metrics.roc_curve(val_Y,bst.predict(xg_val).reshape(val_Y.shape[0], 2)[:,1])
plt.figure()
plt.plot(fpr,tpr,lw=2, color='darkorange',label='ROC curve (area = %0.2f)' % metrics.auc(fpr,tpr))
plt.plot([0, 1], [0, 1], color='navy',lw=2,linestyle='--')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('XGboost Roc curve')
plt.legend(loc="lower right")
plt.savefig("XGboost_ROC.png")
##----------------------------------------------


