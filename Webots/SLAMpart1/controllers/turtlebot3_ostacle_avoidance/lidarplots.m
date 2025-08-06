data = readmatrix('map_points.csv');

% Extract columns
X = data(:,1);
Y = data(:,2);

Xr = data(:,3);
Yr = data(:,4);

% Plot points
figure;
scatter(X, Y, 5, 'filled');  % 5 is marker size, adjust as needed
axis equal;
xlabel('X (m)');
ylabel('Y (m)');
title('Lidar Map Points');
grid on;
hold on;
scatter(Xr, Yr, 5, 'filled');