clear all
% loopspersec = 3;
% seconds = 1;
% t=linspace(0,loopspersec*seconds,seconds*100);

steplength = 0.1;
stepheight = 0.03;
datapoints = 50;

curve = Brazier(steplength, stepheight, datapoints);
xactive=curve(1,:);
zactive=curve(2,:);

t= linspace(xactive(length(xactive)), xactive(1), round(length(xactive)/1.8));
x1 = [xactive(2:length(xactive)-1) t];
x2 = [x1(length(x1)/2:length(x1)) x1(1:length(x1)/2)];
x1 = [x1 x1 x1 x1 x1];
x2 = [x2 x2 x2 x2 x2];


t2= -0.15*ones(1, round(length(zactive)/1.8)-2);
z1= [zactive, t2];
z2 = [z1(length(z1)/2:length(z1)) z1(1:length(z1)/2) ];

z1 = [z1 z1 z1 z1 z1];
z2 = [z2 z2 z2 z2 z2];

length(z1)
length(z2)
length(x1)
length(x2)
%x1 = sin(t*pi*2-pi/2).*0.05;
y = 0.05;
%z1 = -0.15 + cos(t*pi*2-pi/2)/50;

%x2 = sin(t*pi*2+pi/2).*0.05;
%z2 = -0.15 + cos(t*pi*2+pi/2)/50;

l_1 = 0.025;
l_2 = 0.13;
l_3 = 0.015;
l_4 = 0.02;
for n=1:length(x1)
    %V fram H bak
    x1temp= x1(n);
    if(z1(n) > -0.15)
    z1temp=z1(n);
    else
        z1temp=-0.15;
    end
    [alfa,beta,gamma,c_1]=KFunc(x1temp,y,z1temp);
 
    [fot,hoft,kna,havarm_1,havarm_2]=LoopCalc(x1temp,y,z1temp,alfa,beta,gamma,c_1);
    prevalfa = alfa;
    %H fram V bak
    x2temp= x2(n);
    
    if(z2(n) > -0.15)
    z2temp=z2(n);
    else
        z2temp=-0.15;
    end
    
    [alfa2,beta2,gamma2,c_12]=KFunc(x2temp,y,z2temp);
    
    [fot2,hoft2,kna2,havarm2_1,havarm2_2]=LoopCalc(x2temp,y,z2temp,alfa2,beta2,gamma2,c_12);
     prevalfa2 = alfa2;

figure(3)

[xgr ygr] = meshgrid(-1:0.1:1); % Generate x and y data
zgr = -0.15.*ones(size(xgr, 1)); % Generate z data
plane = surf(xgr, ygr, zgr,'FaceAlpha','0.1'); % Plot the surface

hold on

PlotLegs(fot,hoft,kna,havarm_1,havarm_2, 'vfram')
PlotLegs(fot,hoft,kna,havarm_1,havarm_2, 'hbak')
PlotLegs(fot2,hoft2,kna2,havarm2_1,havarm2_2, 'hfram')
PlotLegs(fot2,hoft2,kna2,havarm2_1,havarm2_2, 'vbak')

xlabel('x-led [m]')
ylabel('y-led [m]')
zlabel('z-led [m]')
axis equal
axis ([-0.4 0.1 -0.2 0.1 -0.2 0.05])
view([45, 20])
hold off
  
%     figure(2)
%    
%     plot([0, hoft(1), kna(1), fot(1)], [0, hoft(3), kna(3), fot(3)], 'k', 'LineWidth', 2)   %plot av ben
%      hold on
%     plot([0,0],[0.05,-0.3],'k--')                           %plot av z-axel
%     plot(hoft(1), hoft(3), 'k.', 'MarkerSize', 15)     %plot av hoft-led
%     plot(0, 0, 'k.', 'MarkerSize', 15)                          %plot av hoft-led
%     plot(kna(1), kna(3), 'k.', 'MarkerSize', 15)              %plot av kna-led
%     plot(fot(1), fot(3), 'k.', 'MarkerSize', 25)                      %plot av "fot"
%     plot(havarm_1(1), havarm_1(3), 'k.', 'MarkerSize', 15)              %plot av havarm_1
%     plot(havarm_2(1), havarm_2(3), 'k.', 'MarkerSize', 15)              %plot av havarm_2
%     hold off
%     axis ([-0.2 0.2 -0.3 0.1])
%     xlabel('x-led [m]')
%     ylabel('z-led [m]')
%     title('Sidovy f???r ben')
%     grid on
angl = [alfa, beta, gamma];
end
