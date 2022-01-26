%x=normrnd(0,sqrt(2),1,200);
f=6;%抖动频率
fs=15;%采样频率
N=200;
t=(0:N-1)/fs;
x=sin(2*pi*f*t);%生成抖动偏移序列
X=x+x0;%添加抖动偏移序列后的x方向 
f=7;
fs=15;
N=200;
t=(0:N-1)/fs;
y=sin(2*pi*f*t);
Y=y+y0;%添加抖动偏移序列后的y方向
%yh = hilbert(Y);
%tfr = tfrstft(yh(:), 1:length(yh), 1024);


% 连续小波变换
wavename='cmor3-3';
totalscal=256;
Fc=centfrq(wavename); % 小波的中心频率
