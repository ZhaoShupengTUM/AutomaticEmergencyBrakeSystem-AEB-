%% P-FAS Praktikum Notbremsassistent

%% Data Input
load Messdaten.mat

%% Statische Parameter
a_NB_min = 8;   % [m/s^2] minimale angenommene Verzögerung im Notbremsfall
a_max    = 4;   % [m/s^2] maximal angenommene Manöverbeschleunigung vom Fahrer
t_wirk   = 0.1; % [s] Bremsenverlustzeit, bis a_max [s]
n_traj   = 4;   % Anzahl Trajektorien
result   = zeros(1,n_traj); % Ergebnisvektor (je ein Eintrag pro Trajektorie)

figure
% Durchlauf aller Zeitschritte in Messdaten
for n=1:3:length(x(:,1))
    v_ego = v(n);
    cla
  
    %% Schleife für Durchlauf der Trajektorien:
    for traj = 1:n_traj
        [a_ausw, a_NB] = A1_Vorlage_Erstellung_BA_Beschleunigungen(traj,n_traj,a_NB_min,a_max);
      
        [T, T_i, T_a] = A2_Vorlage_Erstellung_BA_Trajektorie(v_ego, a_ausw, a_NB,t_wirk);
        
        A3_Vorlage_Visualisierung_BA_Trajektorie(T_i, T_a);
        
        [result(traj)] = ML_Check_BA_Trajektorie (T_i, T_a, x(n,:)', y(n,:)');
        
    end
    %% Visualisierung Messdaten
    T1_Plot_Messdaten(x(n,:),y(n,:));
    
    %% Überprüfen der Auslösebedingung (=alle Trajektorien belegt)
   if min(result) == 1
       text(5,0,'STOP', 'Color', 'red', 'FontSize', 15)
       puase (15)
       break
   end 
        
end
