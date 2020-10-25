# market-basket-analysis

## Description
利用訂單資訊記錄每筆訂單內同時擁有的商品,將得到的陣列作轉置並與原陣列作相乘,得到新陣列及代表某商品與某商品同時出現在幾筆訂單中
## Getting Started
### Prerequisites
* numpy
```
$ pip install numpy
```
* 訂單檔案(json format) [點此看更多範例](https://https://github.com/tomhsu2000/market-basket-analysis/tree/main/src)
``` json
[
{	"order": 1,
	"items":[
		{
			"product":"D",
			"Number":2
		},
		{
			"product":"B",
			"Number":1
		}]
},
{	"order": 2,
	"items":[
		{
			"product":"B",
			"Number":2
		},
		{
			"product":"C",
			"Number":3
		}]
},
{	"order": 3,
	"items":[
		{
			"product":"B",
			"Number":2
		},
		{
			"product":"A",
			"Number":0
		}
		,
		{
			"product":"D",
			"Number":2
		}
		]
}
]
```
* 問題檔案(csv format) [點此看更多範例](https://https://github.com/tomhsu2000/market-basket-analysis/tree/main/src)
```
4    # 問題數目
B,D    # 商品名稱
A,C
D,C
C,C
```
### Compile & Execute
#### C++
``` 
$ g++ main.cpp
$ a.exe [訂單檔案] [問題檔案]
```
#### Python
```
$ python main.py [訂單檔案] [問題檔案]
```
## Roadmap

## Known Bugs
