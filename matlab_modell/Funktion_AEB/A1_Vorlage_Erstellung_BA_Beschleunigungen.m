function [a_ausw, a_NB] = A1_Vorlage_Erstellung_BA_Beschleunigungen(traj,n_traj,a_NB_min,a_max)

%Hinweis: Winkel phi definiert analog Skript S. 29, Abb. 7

dphi      =   pi/2/(n_traj-1);          % Schrittweite KAMM'scher Kreis [rad]
phi       =   (traj-1)*dphi;         % Winkel des KAMM'schen Kreises [rad]
 
%% Berechnen von a_ausw aus Fahrerkreis
a_ausw    =    a_max*cos(phi);

%% Berechnen der charakteristischen Größen für ein NB-Manöver
%  a_NB_min ist konstanter Radius des NB-Kreises ("max. resultierende
%  Beschleunigung" 8 m/s^2)
% FZ soll auf a_ausw - Trajektorie bleiben!
a_NB  =  sqrt(a_NB_min^2-a_ausw^2);