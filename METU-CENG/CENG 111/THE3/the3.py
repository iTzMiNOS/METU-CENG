from math import exp

def relu(X):
    return max(0, X)


def sigmoid(X):
    if X <= -700:
        return 0
    elif -700 < X < 700:
        return 1 / (1 + exp(-X))
    elif X > 700:
        return 1


def forward_pass(Network, X):
    x = 0
    for q in range(len(Network)):
        X2 = []
        if len(Network[q]) == 2:
            for j in range(len(Network[q][1])):
                for i in range(len(X)):
                    x += X[i] * Network[q][1][j][i]
                X2.append(x)
                x = 0
            X = X2
        elif Network[q][0] == 'r':
            for o in range(len(X)):
                X[o] = relu(X[o])
        elif Network[q][0] == 's':
            for f in range(len(X)):
                X[f] = sigmoid(X[f])
    return X
