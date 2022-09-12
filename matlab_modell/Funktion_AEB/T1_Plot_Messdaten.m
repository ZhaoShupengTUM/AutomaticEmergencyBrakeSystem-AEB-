function  T1_Plot_Messdaten (x,y)
%% Plotten der Messdaten

hold on
axis equal
axis([-50 +50 -5 105])
plot(y,x,'*')
drawnow

pause(0.5)
