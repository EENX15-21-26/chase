function [curve] = Brazier(steplength,stepheight, datapoints)

P0= [-0.5*steplength; -0.15]; %According to brazier curve for point 1
P1= [-0.712*steplength; -0.15]; % Needs work
P2= [-steplength*0.89; -0.15+stepheight]; % According to brazier curve
P3= [-steplength*0.89; -0.15+stepheight];
P4= [-steplength*0.89; -0.15+stepheight];
P5= [0; -0.15+stepheight];
P6= [0; -0.15+stepheight];
P7= [0; -0.15+stepheight*1.2];
P8= [steplength*0.89; -0.15+stepheight*1.2];
P9= [steplength*0.89; -0.15+stepheight*1.2]; %P2-P9 should be correct
P10= [0.712*steplength; -0.15]; %Needs work
P11= [0.5*steplength; -0.15]; %Ok

Psum = [P0 P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11];
t = linspace(0,1,datapoints);
curve = 0;
for i=0:11
    binom = nchoosek(11,11-i);
    curve = curve + binom.*Psum(:,i+1).*(1-t).^(11-i).*t.^i;
  
   
end
figure
plot(Psum(1,:), Psum(2,:), '--X')

hold on
plot(curve(1,:), curve(2,:), '-')
axis equal
axis ([-0.1 0.1 -0.16 -0.1])
%set(gca,'XTick',[], 'YTick', [])
grid on
hold off