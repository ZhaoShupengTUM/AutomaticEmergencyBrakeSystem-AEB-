function [result] = ML_Check_BA_Trajektorie (T_i, T_a, x, y)
% Überprüft, ob in der ausgewählten Trajektorie (T_i, T_a) ein Messpunkt
% aus x,y liegt.
% 1 = Liegt drin
% 0 = Trajektorie frei

% inpolygon (y_Punkte, x_Punkte, x_Koord_Vektorzug, y_Koord_Vektorzug)
% Der Vektorzug ist die Umrandung der Trajektorie
% Start/Endpunkt ist "innen nah"
    result  = inpolygon(y,x,[T_i(1,:),fliplr(T_a(1,:)),T_i(1,1)],[T_i(2,:),fliplr(T_a(2,:)),T_i(2,1)]);
    result = max(result);
    
    
%Kontrolle
%plot ([T_i(2,:),fliplr(T_a(2,:)),T_i(2,1)],[T_i(1,:),fliplr(T_a(1,:)),T_i(1,1)])
%plot ([-T_i(2,:),fliplr(-T_a(2,:)),T_i(2,1)],[T_i(1,:),fliplr(T_a(1,:)),T_i(1,1)])

    