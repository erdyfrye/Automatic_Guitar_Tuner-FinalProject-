%raw data
D = load('1.txt'); %test=G3
t = D(:,1);
v = D(:,2);
%weighted data arduino
D1 = load('G3 Weight.txt');
t1 = D1(:,1);
v1 = D1(:,2);

%plot raw data
subplot(2,2,1);
plot(t,v);
grid
xlabel('Time (s)')
ylabel('Amplitude')
title('Raw Data (G3)')

%raw data preprocessing 
L = length(t);
Ts = mean(diff(t));                                     % Sampling Interval (sec)
Fs = fix(1/Ts);                                              % Sampling Frequency
Fn = Fs/2;                                              % Nyquist Frequency

%arduino weighted data preprocessing 
L1 = length(t1);
Ts1 = mean(diff(t1));                                     % Sampling Interval (sec)
Fs1 = fix(1/Ts1);                                              % Sampling Frequency
Fn1 = Fs1/2;                                              % Nyquist Frequency

%fungsi windowing matlab
%y=blackmanharris(L);
%vx =v.*y*100;

%plot weighted data arduino
subplot(2,2,2);
plot(t1,v1);
grid
xlabel('Time (s)')
ylabel('Amplitude')
title('Weighted Data (G3)');

%plot weighted data matlab
%subplot(3,2,3);
%plot(t,vx);
%grid
%xlabel('Time (s)')
%ylabel('Amplitude')
%title('Matlab Window');

%FFT weighted data arduino
FTv1 = fft(v1)/L1;                                        % Fourier Transform
Fv1 = linspace(0, Fn1, fix(L1/2)+1);                       % Frequency Vector (Hz)
Iv1 = 1:length(Fv1);                                      % Index Vector

%FFT raw data
%FTv = fft(vx)/L;                                        % Fourier Transform
%Fv = linspace(0, Fn, fix(L/2)+1);                       % Frequency Vector (Hz)
%Iv = 1:length(Fv);                                      % Index Vector

%FFT Raw Data
FTvr = fft(v)/L;                                        % Fourier Transform
Fvr = linspace(0, Fn, fix(L/2)+1);                       % Frequency Vector (Hz)
Ivr = 1:length(Fvr);                                      % Index Vector


%plot hasil fft dari weighted data arduino
subplot(2,2,4)
amp = abs(FTv1(Iv1))*2;
plot(Fv1, amp)
grid
xlabel('Frequency (Hz)')
ylabel('Amplitude')
title('Hasil FFT dengan Window (G3)');
figure(2);
y=ifft(FTv1)
plot(t,y);
%plot hasil fft dari weighted data matlab
%subplot(3,2,5)
%plot(Fv, abs(FTv(Iv))*2)
%grid
%xlabel('Frequency (Hz)')
%%ylabel('Amplitude')
%title('Hasil FFT dari Window Matlab');

%plot hasil fft dari weighted data matlab
subplot(2,2,3)
plot(Fvr, abs(FTvr(Ivr))*2)
grid
xlabel('Frequency (Hz)')
ylabel('Amplitude')
title('Hasil FFT tanpa Window (G3)');