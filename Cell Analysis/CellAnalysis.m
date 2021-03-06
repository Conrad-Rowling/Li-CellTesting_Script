%% Cell Analysis (CA)
%   Written by Tucker Zischka
%   6/14/2021
% This will help to analyze the data captured by the Senior Design Project

clc; clf; clear; close all;

%% Data Import

% 4x.75 ohms = .19
addpath("./Cell Data");

%filesStructure = dir(fileFolder)
%allFileNames = {filesStructure(:).name}
%for k = 1 : length(allFileNames)
%    importfile("Cell2")
%    allFileNames{k}
%end

test1.cell3 = importfile("Cell3 4 .75ohm.csv", [3, Inf]);
test1.cell4 = importfile("Cell4 4 .75ohm.csv", [3, Inf]);
test1.cell5 = importfile("Cell5 4 .75ohm.csv", [3, Inf]);
test1.cell6 = importfile("Cell6 4 .75ohm.csv", [3, Inf]);
test1.cell7 = importfile("Cell7 4 .75ohm.csv", [3, Inf]);
test1.cell8 = importfile("Cell8 4 .75ohm.csv", [3, Inf]);
test1.cell9 = importfile("Cell9 4 .75ohm.csv", [3, Inf]);
test1.cell10 = importfile("Cell10 4 .75ohm.csv", [3, Inf]);

%% Calculate Call

[averageShuntMV, shuntRegression] = calculateAvg(test1, 'VShuntmV');
[averageBatMV , batRegression] = calculateAvg(test1, 'VbatValmV');

range = 1:5:574;
shunt = shuntRegression(range); 
bat = batRegression(range);

shunt = shunt .* 1.2; 
bat = bat ./ 1000; 

power = shunt .* bat; 

energy_Consumed = zeros(numel(power), 1); 

for i = 1:numel(power)
    for j = 1:i
       energy_Consumed(i) = energy_Consumed(i) + power(j)*.5; 
    end
end


[averageTemp{1}, tempReg1] = calculateAvg(test1, 'BatteryTemp1');
[averageTemp{2}, tempReg2] = calculateAvg(test1, 'BatteryTemp2');
[averageTemp{3}, tempReg3] = calculateAvg(test1, 'BatteryTemp3');
[averageTemp{4}, tempReg4] = calculateAvg(test1, 'BatteryTemp4');

averageTempMatrix(:,1) = tempReg1(range);
averageTempMatrix(:,2) = tempReg2(range);
averageTempMatrix(:,3) = tempReg3(range);
averageTempMatrix(:,4) = tempReg4(range);

[X,Y] = meshgrid([1 2 3 4], energy_Consumed');
figure; 
surf(X, Y, averageTempMatrix);
xlabel('Cell Body Position');
ylabel('Energy Consumed [Joules]');
zlabel('Temperature [C]');
title('Temperature Profile vs Energy Consumed');
hold on; 

%% Functions
function void = heatCalc(test1)
% Temp Averaging
averageTemp{1} = calculateAvg(test1, 'BatteryTemp1');
averageTemp{2} = calculateAvg(test1, 'BatteryTemp2');
averageTemp{3} = calculateAvg(test1, 'BatteryTemp3');
averageTemp{4} = calculateAvg(test1, 'BatteryTemp4');

curveFit = calcTempAvg(averageTemp);

m_c = 46.6./1000;     % mass [Kgrams]
c_p = 1108.4;   % Specific Heat Capacity [J/Kg*K]
delta_t = curveFit(547) - curveFit(0);     % Change in Temperature [Delta T]

ambient_temps = calculateAvg(test1, 'ResistorTemp0'); 

ambient_temp_avg = mean(ambient_temps); 
area_cell = .0037573;                       % Area of a cell  [m^2]

% Move over the 
for i = 1:numel(ambient_temps(:,1))
    ambient_delta_t(i,2) = curveFit(ambient_temps(i,1)) - ambient_temp_avg(1,2);    
end

% move over the time
ambient_delta_t(:,1) = ambient_temps(:,1);

% h_conv = %1.32 .* (ambient_delta_t ./ 65 ).^(.25);       % convection transfer coefficient for a cylinder [W/(m^2*C)]
h_conv = ones(numel(ambient_delta_t(:,1)),2);              % Setting everything to ones 


Q_gen = m_c .* c_p * delta_t;
q_loss = [ambient_delta_t(:,1) (h_conv(:,2) .* area_cell .* ambient_delta_t(:,2))];
Q_loss = trapz(q_loss(:,1),q_loss(:,2));
end

function regressionFit = calcTempAvg(averageTemp)
totalTemp = [];
for i = 1:numel(averageTemp)
    totalTemp = cat(1, totalTemp, averageTemp{i} );
end

% Sort the items
totalTemp = sortrows(totalTemp);

% Remove NaNs
totalTemp = rmmissing(totalTemp);

% Regression Fit 
regressionFit = fit(totalTemp(:,1), totalTemp(:,2), 'gauss7');

%% Graph the Average Temperature

figure;
plot(regressionFit);
xlim([1 547]);
xlabel('Time [Seconds]');
ylabel('Temperature [Celcius]');
title('Average Temp vs Time');
hold on; 
end

function [testSet, regressionFit] = calculateAvg(test1 , dataName)
fn = fieldnames(test1);

%% Preprocess Time
for i = 1:numel(fn)
   [peaks, peakLocs] = findpeaks(test1.(fn{i}).Times);
   for j = 1:numel(peakLocs)
       if j == numel(peakLocs)
           endPoint = numel(test1.(fn{i}).Times); 
       else
           endPoint = peakLocs(j+1);
       end
       for k = peakLocs(j) + 1 : endPoint
            test1.(fn{i}).Times(k) = test1.(fn{i}).Times(k) + 500 .* j;
       end
   end
end

%% Average Current vs Time

%Dump everything into one 
totalCurrent = [];
for i = 1:numel(fn)
    totalCurrent = cat(1, totalCurrent, [test1.(fn{i}).Times, test1.(fn{i}).(dataName)]);
end

% Sort the items
totalCurrent = sortrows(totalCurrent);

% Remove NaNs
totalCurrent = rmmissing(totalCurrent);

% Regression Fit 
regressionFit = fit(totalCurrent(:,1), totalCurrent(:,2), 'gauss8');

%{
% Bin the Items
binEdges = 0:1:ceil(totalCurrent(end,1)); 
totalBins = numel(binEdges); 
bins = discretize(totalCurrent(:,1), binEdges);

summedCurrent = zeros([totalBins , 2]); 
old = bins(1);
numberToAverage = 0; 
for i = 1:numel(bins)                                                      %iteraterate through the entire sorted set
    summedCurrent(bins(i),:) = summedCurrent(bins(i),:) + totalCurrent(i,:);    % Sum the sorted set together in the bins they belong to
    numberToAverage = numberToAverage + 1;                                      % Keep track of how much to average
    if old ~= bins(i)                                                           % Average them once you reached the end of the bing
        old = bins(i);
        summedCurrent(bins(i-1),:) = summedCurrent(bins(i-1),:) ./ numberToAverage; 
        numberToAverage = 0; 
    end
end

summedCurrent(bins(end, 1),:) = summedCurrent(bins(end,1),:) ./ numberToAverage; 
%}

%% Graph The Average Current

figure;
%set(gca, 'FontSize', fsz, 'LineWidth', alw); %<- Set properties
plot(regressionFit);
%set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); %<- Set size

%plot(summedCurrent(:,1),summedCurrent(:,2), 'LineWidth',lw,'MarkerSize',msz); %<- Specify plot properites
xlim([1 547]);
xlabel('Time [Seconds]');
ylabel('Voltage [milliVolts]');
title(strcat({'Average '}, dataName, {' vs Time'}));
hold on; 

%% Function Return 
testSet = totalCurrent; 
end

function cell2475ohm1 = importfile(filename, dataLines)
%% Input handling

% If dataLines is not specified, define defaults
if nargin < 2
    dataLines = [3, Inf];
end

%% Set up the Import Options and import the data
opts = delimitedTextImportOptions("NumVariables", 20);

% Specify range and delimiter
opts.DataLines = dataLines;
opts.Delimiter = ",";

% Specify column names and types
opts.VariableNames = ["Times", "VbatValmV", "VbatHighmV", "VbatLowmV", "VShuntmV", "VShuntGNDmV", "VRefmV", "Gain", "ShuntG", "BatteryTemp0", "BatteryTemp1", "BatteryTemp2", "BatteryTemp3", "BatteryTemp4", "BatteryTemp5", "ResistorTemp0", "ResistorTemp1", "ResistorTemp2", "ResistorTemp3", "ResistorTemp4"];
opts.VariableTypes = ["double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double"];

% Specify file level properties
opts.ExtraColumnsRule = "ignore";
opts.EmptyLineRule = "read";

% Import the data
cell2475ohm1 = readtable(filename, opts);

end