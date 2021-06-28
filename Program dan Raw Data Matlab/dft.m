clc;
clear all;
close all;
xn=input('enter sequence = ');
N=input('enter value of N = ');
Xk=dft_fun(xn,N);
k=0:N-1;
subplot(2,1,1)
stem(k,abs(Xk))
xlabel('k')
ylabel('[Xk]')
title('magnitude plot')
subplot(2,1,2)
stem(k,angle(Xk))
xlabel('k')
ylabel('anlge (Xk)')
title('phase plot')