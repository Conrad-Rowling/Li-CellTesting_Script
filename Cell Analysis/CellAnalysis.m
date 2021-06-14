%% Cell Analysis (CA)
%   Written by Tucker Zischka
%   6/14/2021
% This will help to solve for resistance in the busbar/bolted joints of the
% accumulator 

clc; clear; close all;
%% Data Import

% 4x.75 ohms = .19
addpath('.\Cell Data')
test1.cell2 = importfile("Cell2 4 .75ohm.csv", [3, Inf]);
test1.cell3 = importfile("Cell3 4 .75ohm.csv", [3, Inf]);
test1.cell4 = importfile("Cell4 4 .75ohm.csv", [3, Inf]);
test1.cell5 = importfile("Cell5 4 .75ohm.csv", [3, Inf]);
test1.cell6 = importfile("Cell6 4 .75ohm.csv", [3, Inf]);
test1.cell7 = importfile("Cell7 4 .75ohm.csv", [3, Inf]);
test1.cell8 = importfile("Cell8 4 .75ohm.csv", [3, Inf]);
test1.cell9 = importfile("Cell9 4 .75ohm.csv", [3, Inf]);
test1.cell10 = importfile("Cell10 4 .75ohm.csv", [3, Inf]);

fn = fieldnames(test1);
for i = 1:numel(fn)  
    %test2.(fn{i}) = test1.(fn{i});
end 

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
    totalCurrent = cat(1, totalCurrent, [test1.(fn{i}).Times, test1.(fn{i}).VShuntmV]);
end

% Sort the items
totalCurrent = sortrows(totalCurrent);

% Remove NaNs
totalCurrent = rmmissing(totalCurrent);

% Bin the Items
totalBins = 1000; 
[bins, edges] = discretize(totalCurrent, totalBins);

summedCurrent = zeros([totalBins , 2]); 
old = bins(1);
numberToAverage = 0; 
for i = 1:numel(bins(:,1))    %iteraterate through the entire sorted set
    summedCurrent(bins(i),:) = summedCurrent(bins(i),:) + totalCurrent(i,:);    % Sum the sorted set together in the bins they belong to
    numberToAverage = numberToAverage + 1;                                      % Keep track of how much to average
    if old ~= bins(i)                                                           % Average them once you reached the end of the bing
        old = bins(i);
        summedCurrent(bins(i-1),:) = summedCurrent(bins(i-1),:) ./ numberToAverage; 
        numberToAverage = 0; 
    end
end

%% Graph The Average Current

% Plot Properties
width = 3;     % Width in inches
height = 3;    % Height in inches
alw = 0.75;    % AxesLineWidth
fsz = 11;      % Fontsize
lw = 1.5;      % LineWidth
msz = 8;       % MarkerSize

figure(1);
pos = get(gcf, 'Position');
%set(gcf, 'Position', [pos(1) pos(2) width*100, height*100]); %<- Set size
set(gca, 'FontSize', fsz, 'LineWidth', alw); %<- Set properties
plot(summedCurrent(:,1),summedCurrent(:,2), 'LineWidth',lw,'MarkerSize',msz); %<- Specify plot properites
xlim([1 547]);
xlabel('Time [Seconds]');
ylabel('Shunt Voltage [milliVolts]');
title('Average Shunt Voltage vs Time');

%% Functions
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