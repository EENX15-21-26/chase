clear all
figure(1)
clf
figure(2)
clf
figure(3)
clf
clc


% Givet
l_1 = 0.025;
l_2 = 0.13;
l_3 = 0.015;
l_4 = 0.02;

x = 0.1;
y = 0.1;
z = -0.15;

% Hjälpekvationer
c_1 = sqrt(x^2 + y^2 + z^2-l_1^2);
c_2 = sqrt((l_2+l_4)^2-(l_4*c_1^2/l_2));
c_3 = acos((l_2^2+l_3^2-c_2^2)/(2*l_2*l_3));
c_4 = sqrt(2*(l_2^2*l_3^2+ l_2^2*c_2^2+l_3^2*c_2^2)-l_2^4-l_3^4-c_2^4)/4;
c_5 = sqrt(2*(l_2^2*l_4^2+ l_2^2*c_2^2+l_4^2*c_2^2)-l_2^4-l_4^4-c_2^4)/4;

% Alpha
alpha = acos(c_1/(2*l_2)) - asin(x/c_1);

% Gamma
gamma = pi/2 + acos(y / sqrt(y^2 + z^2)) - acos(l_1 / sqrt(y^2 + z^2));

% Beta
beta = c_3 - alpha + asin((2 * c_4)/(l_2*c_2)) - asin((2*c_5)/(l_2*c_2));


% Ledposition (för plottning)
a1 = acos(c_1/(2*l_2));
a2 = asin(x/c_1);

ll = l_2 * cos(alpha);
aa = atan(ll/l_1);
hyp = sqrt(ll^2+l_1^2);

fot = [x, y, z];
hoft = [0, l_1 * sin(gamma), l_1 * cos(gamma)];
kna = [-l_2 * sin(alpha), hyp * sin(pi - gamma - aa), -hyp * cos(pi - gamma - aa)];
havarm_1 = hoft + l_3 * [-sin(beta), -sin(pi/2 - gamma) * cos(beta), cos(pi/2 - gamma) * cos(beta)];
havarm_2 = kna + l_4 * [-cos(pi/2-a1-a2), -sin(pi/2 - gamma) * sin(pi/2-a1-a2), cos(pi/2 - gamma) * sin(pi/2-a1-a2)];

figure(1)
hold on
plot([0, hoft(2), kna(2), fot(2)], [0, hoft(3), kna(3), fot(3)], 'k', 'LineWidth', 2)   %plot av ben
plot([0,0],[0.05,-0.3],'k--')                           %plot av z-axel
plot(hoft(2), hoft(3), 'k.', 'MarkerSize', 15)     %plot av h�ft-led
plot(0, 0, 'k.', 'MarkerSize', 15)                          %plot av h�ft-led
plot(kna(2), kna(3), 'k.', 'MarkerSize', 15)              %plot av kn�-led
plot(fot(2), fot(3), 'k.', 'MarkerSize', 25)                      %plot av "fot"
plot(havarm_1(2), havarm_1(3), 'k.', 'MarkerSize', 15)              %plot av hävarm_1
plot(havarm_2(2), havarm_2(3), 'k.', 'MarkerSize', 15)              %plot av hävarm_1
axis equal
xlabel('y-led [m]')
ylabel('z-led [m]')
title('Frontvy f�r ben')
grid on



figure(2)
hold on
plot([0, hoft(1), kna(1), fot(1)], [0, hoft(3), kna(3), fot(3)], 'k', 'LineWidth', 2)   %plot av ben
plot([0,0],[0.05,-0.3],'k--')                           %plot av z-axel
plot(hoft(1), hoft(3), 'k.', 'MarkerSize', 15)     %plot av h�ft-led
plot(0, 0, 'k.', 'MarkerSize', 15)                          %plot av h�ft-led
plot(kna(1), kna(3), 'k.', 'MarkerSize', 15)              %plot av kn�-led
plot(fot(1), fot(3), 'k.', 'MarkerSize', 25)                      %plot av "fot"
plot(havarm_1(1), havarm_1(3), 'k.', 'MarkerSize', 15)              %plot av hävarm_1
plot(havarm_2(1), havarm_2(3), 'k.', 'MarkerSize', 15)              %plot av hävarm_2
axis equal
xlabel('x-led [m]')
ylabel('z-led [m]')
title('Sidovy f�r ben')
grid on


disp("Alpha")
disp(alpha*180/pi)
disp("Beta")
disp(beta*180/pi)
disp("Gamma")
disp(gamma*180/pi)

figure(3)
plot3([0, hoft(1), kna(1), fot(1)],[0, hoft(2), kna(2), fot(2)], [0, hoft(3), kna(3), fot(3)])

hold on
plot3([hoft(1), havarm_1(1), havarm_2(1), kna(1)],[hoft(2), havarm_1(2), havarm_2(2), kna(2)], [hoft(3), havarm_1(3), havarm_2(3), kna(3)])
xlabel('x-led [m]')
ylabel('y-led [m]')
zlabel('z-led [m]')
axis equal

l1 = sqrt(sum((kna-hoft).^2))
l2 = sqrt(sum((fot-kna).^2))

h = sqrt(sum((havarm_1-havarm_2).^2))
h1 = sqrt(sum((hoft-havarm_1).^2))
h2 = sqrt(sum((kna-havarm_2).^2))


