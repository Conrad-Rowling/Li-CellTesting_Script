%% Resistances of an Accumulator 
%   Written by Tucker Zischka
%   8/2/2020
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

%% Average Current vs Time
test1.shuntMV = zeros(length(test1));
for i = 1:numel(fn)
    test1(i,:).shuntMV = test1.(fn{i}).VShuntmV;
end



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