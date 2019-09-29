#!/usr/bin/env python
# coding: utf-8

# ## Optimización, PCA y Regresión
# 

# # Metodo de la Biseccion

# In[1]:


#Definicion de la funcion
def p(x):
    return x**3-x-1
    
#Definicion de parametros
a=-1
b=2
error=10
i=0
while error > 1e-8:
    c = (a+b)/2
    fa = p(a)
    fc = p(c)
    if fc == 0:
        raiz = c
        break
    elif fa * fc < 0:
        b = c
    else:
        a = c
    raiz = c
    i += 1
    error = abs(fc)
    print("Iteracion",i,"- Raiz aproximada", raiz)

print(raiz)
        


# In[3]:


import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(-5,5,101)
print(x)
plt.plot(x,p(x))
plt.grid()
plt.show()


# # Numero de condicion Matriz de Hilbert

# In[3]:


#Funcion para obtener la matriz de hilbert
def hilb(n, m=0):
    if n < 1 or m < 0:
        raise ValueError("Matrix size must be one or greater")
    elif n == 1 and (m == 0 or m == 1):
        return np.array([[1]])
    elif m == 0:
        m = n

    v = np.arange(1, n + 1) + np.arange(0, m)[:, np.newaxis]
    return 1. / v

hilbert_matrix = hilb(20,20)


# In[4]:




for i in range(3, 21):
    m = hilb(i)
    print("n=",i,"numero de condicion=", np.linalg.cond(m))


# # PCA

# In[8]:


#Importando librerias
import numpy as np # linear algebra
import pandas as pd 
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
from sklearn.metrics import accuracy_score
import os
from sklearn import preprocessing


df=pd.read_csv("wine.csv")
df.head()
df.shape
X = df.iloc[:, 1:12].values
y = df.iloc[:, 12].values

from sklearn.model_selection import train_test_split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.25, random_state = 0)

from sklearn.preprocessing import StandardScaler
sc = StandardScaler()
X_train = sc.fit_transform(X_train)
X_test = sc.transform(X_test)

# Applying PCA
from sklearn.decomposition import PCA
pca = PCA(n_components = 3)
X_train = pca.fit_transform(X_train)
X_test = pca.transform(X_test)
explained_variance = pca.explained_variance_ratio_

print(explained_variance)

lab_enc = preprocessing.LabelEncoder()
training_scores_encoded = lab_enc.fit_transform(y_train)

from sklearn.linear_model import LogisticRegression
clf = LogisticRegression()
clf.fit(X_train, training_scores_encoded)
print("LogisticRegression")
lr_pred = clf.predict(X_test)
print(clf.predict(X_test))
#lr_c=LogisticRegression(random_state=0)
#lr_c.fit(X_train,training_scores_encoded)
#lr_pred=lr_c.predict(X_test)
#lr_cm=confusion_matrix(y_test,lr_pred)



# In[25]:


from numpy import linalg as la
mat = np.array([[0, 2 ],
              [2, 0 ],
              [3, 1 ],
              [1, 3 ],
             ]
            )
np.linalg.matrix_rank(mat)
print(mat)

U, s, Vh = np.linalg.svd(mat)
print(U.shape, Vh.shape, s.shape)
print(U, s, Vh)

def vector_unit(n):
    vec = np.random.randn(n,)
    tam = la.norm(vec)
    return np.array([x/tam for x in vec])

def svd_ld(A):
    n,m = A.shape
    x = vector_unit(m)
    uv = None
    av = x
    B = np.dot(A.T,A)
    i = 0
    while True:
        i+= 1
        uv = av
        av = np.dot(B, uv)
        av /= la.norm(av)
        if(abs(np.dot(av,uv)) > 1 - 1e-5):
            return av

svd_ld(mat)


# In[38]:


from sklearn.datasets import make_classification
X, y = make_classification(n_samples =100,
    n_features =1,
    n_classes =2,
    n_informative=1,
    n_redundant =0,
    n_repeated =0,
    n_clusters_per_class =1,
    random_state = 12)
X = np.hstack( ( np.ones_like(X),X) )

def sigmoide(x):
    num = 1.
    den = 1+np.exp(-x)
    return num/den

def dsigmoide(y):
    op1=1-sigmoide(y)
    op2=sigmoide(y)*op1
    return op2

h = lambda Z:sigmoide(Z)

def J(Y,Yp):
    L = (Y* np.log(Yp) + (Y-1) * np.log(1 -Yp)).mean()
    return L
    
def grad(X,Y,Yp):
    delta = Yp - Y.reshape(-1,1)
    return np.dot(X.T, delta) / X.shape[0]

E = []
epocas = 2000
ca = 0.1
T = np.random.ranf((2,1))
print("Pesos iniciales")
for i in range(epocas):
    yp = sigmoide(np.dot(X,T))
    derivs = grad(X,y,yp)
    T[0] -= ca*derivs[0]
    T[1] -= ca*derivs[1]
    error = J(y, yp)
    E.append(error)
    print("{}".format(error))
    
print(T)

