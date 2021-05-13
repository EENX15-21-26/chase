function [alfa,beta,gamma,c_1] = KFunc(x,y,z)

l_1 = 0.0358;
l_2 = 0.13;
l_3 = 0.024;
l_4 = 0.024;

    % Hj??lpekvationer
c_1 = sqrt(x.^2 + y.^2 + z.^2-l_1.^2);
c_2 = sqrt((l_2+l_4).^2-(l_4.*c_1.^2./l_2));
c_3 = acos((l_2.^2+l_3.^2-c_2.^2)./(2*l_2.*l_3));
c_4 = sqrt(2*(l_2.^2*l_3.^2+ l_2.^2*c_2.^2+l_3.^2*c_2.^2)-l_2.^4-l_3.^4-c_2.^4)./4;
c_5 = sqrt(2*(l_2.^2*l_4.^2+ l_2.^2*c_2.^2+l_4.^2*c_2.^2)-l_2.^4-l_4.^4-c_2.^4)./4;

% Alpha
alfa = acos(c_1/(2*l_2)) - asin(x./c_1);

% Gamma
gamma = pi/2 + acos(y./sqrt(y.^2 + z.^2)) - acos(l_1./sqrt(y.^2 + z.^2));

% Beta
beta = c_3 - alfa + asin((2 * c_4)./(l_2.*c_2)) - asin((2*c_5)./(l_2.*c_2));

vinklar = [alfa, beta, gamma]
end