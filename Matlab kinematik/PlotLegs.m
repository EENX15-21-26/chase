function plot = PlotLegs(fot,hoft,kna,havarm_1,havarm_2, leg)


%Hbak
switch leg
    case 'vbak'
    plot3([0, hoft(1), kna(1), fot(1)]-0.204,[0, hoft(2), kna(2), fot(2)], [0, hoft(3), kna(3), fot(3)])  
   
    plot3([hoft(1), havarm_1(1), havarm_2(1), kna(1)]-0.204,[hoft(2), havarm_1(2), havarm_2(2), kna(2)], [hoft(3), havarm_1(3), havarm_2(3), kna(3)])

%Hfram
case 'vfram'
    plot3([0, hoft(1), kna(1), fot(1)],[0, hoft(2), kna(2), fot(2)], [0, hoft(3), kna(3), fot(3)])
  
    plot3([hoft(1), havarm_1(1), havarm_2(1), kna(1)],[hoft(2), havarm_1(2), havarm_2(2), kna(2)], [hoft(3), havarm_1(3), havarm_2(3), kna(3)])


%Vbak
case 'hbak'  
    plot3([0, hoft(1), kna(1), fot(1)]-0.204,-([0, hoft(2), kna(2), fot(2)]+0.0836), [0, hoft(3), kna(3), fot(3)])
   
    plot3([hoft(1), havarm_1(1), havarm_2(1), kna(1)]-0.204,-([hoft(2), havarm_1(2), havarm_2(2), kna(2)]+0.0836), [hoft(3), havarm_1(3), havarm_2(3), kna(3)])

    %Vfram
case 'hfram'  
    plot3([0, hoft(1), kna(1), fot(1)],-([0, hoft(2), kna(2), fot(2)]+0.0836), [0, hoft(3), kna(3), fot(3)])

    plot3([hoft(1), havarm_1(1), havarm_2(1), kna(1)],-([hoft(2), havarm_1(2), havarm_2(2), kna(2)]+0.0836), [hoft(3), havarm_1(3), havarm_2(3), kna(3)])
    otherwise disp('error')
end
   