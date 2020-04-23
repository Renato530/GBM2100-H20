function [] = uart()


%%%%%%%%%%%%%%%%%%%%%%%%
% Supposons que le format de la chaîne de caractères envoyés
% est la suivante :
%   "%d\t%d\t%d\n"
% Où les valeurs numériques sont comme suivent:
% 1 - %d : 	Identifiant
% 2 - %d :	Numéro de l'essai
% 3 - %d :	Temps de réaction
%%%%%%%%%%%%%%%%%%%%%%%

clear;
clc;

    %   Pour que le code de nettoyage ait acces a notre port
    %   serie, cette variable doit etre globale

global serialPort;
    
fprintf('Appuyez sur ENTRER pour quitter\n');
    
    %  Donnons a notre programme une fonction de nettoyage
    %  En cas d_erreur, celle-ci aura comme role de fermer le
    %  le port serie

c = onCleanup(@()cleanup);
    
    %   Cette section permet d'ouvrir le port serie de votre
    %   ordinateur. Remplacer 'COMX' ou X est le numero du
    %   du port serie a ouvrir. Le baudrate est de 115200.
    %   Si vous configurez votre port UART assurez-vous
    %   de corriger le Baudrate de votre code Matlab.
    %
serialPort = serial("COMX");
set(serialPort,'BaudRate',115200);
fopen(serialPort);

while (true)
	%Acquisition de donnees sur le port
	out = fscanf(serialPort);

	%exemple pour séparer les données reçues avec split
	%.... à un tab
	out = regexp(out,'\t','split');

	%.... à un espace: out = char(regexp(out,' ','split'));

	if(length(out) < 3)
		continue;
	end;
        
	id = str2double(out(1));
	essai = str2double(out(2));
	duree = str2double(out(3));

%%%%%%%%%%%%%%%%%%%%%%%%%%	Votre traitement

	% Voyons si l_usage veut quitter

	isKeyPressed = ~isempty(get(h,'CurrentCharacter'));
	if isKeyPressed
		break
	end
end
end
%--------------------------------
function [] = cleanup()
   global serialPort;
   fprintf('Cleaning up:...\n');
   %Fermeture du port serie
   fclose(serialPort);
end