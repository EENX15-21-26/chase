function [fot,hoft,kna,havarm_1,havarm_2] = LoopCalc(x,y,z,alfa,beta,gamma,c_1)
l_1 = 0.0358;
l_2 = 0.13;
l_3 = 0.024;
l_4 = 0.024;

ll = l_2 * cos(alfa);
    aa = atan(ll/l_1);
    hyp = sqrt(ll^2+l_1^2);
    
    a1 = acos(c_1./(2.*l_2));
    a2 = asin(x./c_1);
    fot = [x, y, z];
    hoft = [0, l_1 * sin(gamma), l_1 * cos(gamma)];
    kna = [-l_2 * sin(alfa), hyp * sin(pi - gamma - aa), -hyp * cos(pi - gamma - aa)];
    havarm_1 = hoft + l_3 * [-sin(beta), -sin(pi/2 - gamma) * cos(beta), cos(pi/2 - gamma) * cos(beta)];
   
    havarm_2 = kna + l_4 .* [-cos(pi/2-a1-a2), -sin(pi/2 - gamma) .* sin(pi./2-a1-a2), cos(pi/2 - gamma) .* sin(pi/2-a1-a2)];
end