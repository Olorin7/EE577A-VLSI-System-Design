wset = load('dram.txt');
wset = abs(wset);

RTL = wset(1:2, :);
Iavg = wset(3:4, :);
Pavg = wset(5:6, :);

minRTL = min(min(RTL));
maxRTL = max(max(RTL));
stdRTL = std(std(RTL));
avgRTL = mean(mean(RTL));

minIavg = min(min(Iavg));
maxIavg = max(max(Iavg));
stdIavg = std(std(Iavg));
avgIavg = mean(mean(Iavg));

minPavg = min(min(Pavg));
maxPavg = max(max(Pavg));
stdPavg = std(std(Pavg));
avgPavg = mean(mean(Pavg));