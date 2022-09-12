function [T, T_i, T_a] = A2_Vorlage_Erstellung_BA_Trajektorie(v_ego, a_ausw,...
                            a_NB,t_wirk)
% Erstellung von möglichen Ausweichtrajektorien - Herleitung

%% Fahrzeug-Parameter
s_Luft = 1;
w = 12;
b_T = 2/2 + s_Luft; 



%% Kreisbahn
% Beschleunigung a_y = const
% Für jeden Endzeitpunkt t_end existiert eine feste Gradzahl phi,
% unabhängig von r.
% Berechnung Kreisbahnradius:

r = v_ego^2/a_ausw;
r = max(w/2,r);

% Berechnung Kreissegmentlänge = Bremsweg s_b:
s_b = v_ego * t_wirk + s_Luft + v_ego^2 / (2*a_NB);
gamma_max = s_b/r;
gamma = linspace(0,gamma_max,16);

%% Berechnung der Trajektorien T, T_i und T_a

T = [r*(1-cos(gamma)); r*sin(gamma)];

T_i = [ b_T + (r-b_T)*(1-cos(gamma));  (r-b_T)*sin(gamma) ];

T_a = [ -b_T + (r+b_T)*(1-cos(gamma))   ; (r+b_T)*sin(gamma) ];



%% Kontrolle (für Tutor)
% plot (T_a(1,:), T_a(2,:), T_i(1,:), T_i(2,:))
