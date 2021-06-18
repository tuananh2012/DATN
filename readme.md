## Chạy thử nghiệm

### So sánh kết quả tích phân 

```sh
g++ testIntegral.cpp -o a 
./a
```
### Chạy thực nghiệm 3 thuật toán với 5 làn đường


```sh
g++ fiveLanesComparision.cpp 
./fiveLanesComparision
```
### So sánh chi tiết 3 thuật toán khi Cij thay đổi
```sh
g++ multiLaneForCompareThreeAlgorithm.cpp
./multiLaneForCompareThreeAlgorithm
```
Các thông số đầu vào cho bài toán khá đơn giản có thể được sửa trực tiếp trong file code.
Em cũng cài đặt sẵn một thư viện tối ưu với thuật toán ABC và PSO, tương ứng là 2 thuật toán biến thể của PSO và ABC có thể được gọi bằng phương thức optimizer1()
### plot các kết quả
```sh
cd CompareResult
python plot.py
```
hoặc 
```sh
cd PlotData
python plot.py
```
### Thử nghiệm kết quả tính toán với giả lập phân phối Poisson 2 chiều
```sh
python generateData.py
g++ verifyAnswer.cpp 
./ verifyAnser
```