import json
import numpy as np
import sys

orderList = {}
orderMat = []
questions = []

def main():
    loadJsonFile()
    loadTxtFile()
    adj = calculateResult()
    for ques in questions:
        print(adj[orderList[ques[0]]][orderList[ques[1]]])

def loadJsonFile():
    inputFile = open(sys.argv[1])
    orders = json.load(inputFile)
    orderMap = {}
    for order in orders:
        orderNum = order["order"]
        for item in order["items"]:
            if item["product"] not in orderMap:
                orderMap[item["product"]] = []
                orderList[item["product"]] = len(orderList)
            orderLen = len(orderMap[item["product"]])
            if orderLen < orderNum:
                for x in range(orderLen, orderNum):
                    orderMap[item["product"]].append(0)
            if item["Number"] != 0:
                orderMap[item["product"]][orderNum-1] = 1
    totalOrder = len(orders)
    for product in orderMap:
        orderLen = len(orderMap[product])
        if orderLen < totalOrder:
            for x in range(orderLen, totalOrder):
                    orderMap[product].append(0)
        orderMat.append(orderMap[product])

def calculateResult():
    mat = np.array(orderMat)
    adj = np.dot(mat, mat.T)
    return adj

def loadTxtFile():
    inputFile = open(sys.argv[2])
    quesNum = int(inputFile.readline())
    for x in range(quesNum):
        ques = inputFile.readline().strip().split(",")
        questions.append(ques)

if __name__ == "__main__":
    main()
