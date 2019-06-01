wset = load('dram.txt');
wset = abs(wset);
Fin = [1:4:5];
C = zeros(1,11);
for i = 1:11
    C(i) = power(50000, (i-1)/10.0);
end
[C, Fin] = meshgrid(C, Fin);
RTL = wset(1:2, :);
Iavg = wset(3:4, :);
Pavg = wset(5:6, :);

figure(1);
g1 = surf(C, Fin, RTL);
figure(2);
g2 = surf(C, Fin, Iavg);
figure(3);
g3 = surf(C, Fin, Pavg);