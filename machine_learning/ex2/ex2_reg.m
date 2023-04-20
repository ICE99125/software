%% Machine Learning Online Class - Exercise 2: Logistic Regression
%
%  Instructions
%  ------------
% 
%  This file contains code that helps you get started on the second part
%  of the exercise which covers regularization with logistic regression.
%
%  You will need to complete the following functions in this exericse:
%
%     sigmoid.m
%     costFunction.m
%     predict.m
%     costFunctionReg.m
%
%  For this exercise, you will not need to change any code in this file,
%  or any other files other than those mentioned above.
%

%% Initialization
clear ; close all; clc

%% Load Data
%  The first two columns contains the X values and the third column
%  contains the label (y).

data = load('ex2data2.txt');
X = data(:, [1, 2]); y = data(:, 3);

plotData(X, y);

% Put some labels 
hold on;

% Labels and Legend
xlabel('Microchip Test 1');
ylabel('Microchip Test 2');

% Specified in plot order
legend('y = 1', 'y = 0')
hold off;


%% =========== Part 1: Regularized Logistic Regression ============
%  In this part, you are given a dataset with data points that are not
%  linearly separable. However, you would still like to use logistic 
%  regression to classify the data points. 
%
%  To do so, you introduce more features to use -- in particular, you add
%  polynomial features to our data matrix (similar to polynomial
%  regression).
%

% Add Polynomial Features

% Note that mapFeature also adds a column of ones for us, so the intercept
% term is handled
X = mapFeature(X(:,1), X(:,2));

% Initialize fitting parameters
initial_theta = zeros(size(X, 2), 1);
% initial_theta = [
%   0
%   0
%   ...
% ]

% Set regularization parameter lambda to 1
lambda = 1; % 正则化参数

% Compute and display initial cost and gradient for regularized logistic
% regression
[cost, grad] = costFunctionReg(initial_theta, X, y, lambda);

fprintf('initial_theta 时的代价: %f\n', cost);
fprintf('期待值(大约): 0.693\n');

fprintf('initial_theta 处的梯度, 仅前 5 个:\n');
fprintf('%f \n', grad(1:5));
fprintf('期待梯度(大约), 仅前 5 个:\n');
fprintf('0.0085\n0.0188\n0.0001\n0.0503\n0.0115\n');

fprintf('\n按回车继续.\n');
pause;

% Compute and display cost and gradient with non-zero theta
test_theta = ones(size(X,2), 1);
[cost, grad] = costFunctionReg(test_theta, X, y, lambda);

fprintf('test_theta 时的代价: %f\n', cost);
fprintf('期待值(大约): 2.13\n');

fprintf('test_theta 处的梯度, 仅前 5 个:\n');
fprintf('%f \n', grad(1:5));
fprintf('期待梯度(大约), 仅前 5 个:\n');
fprintf('0.3460\n0.0851\n0.1185\n0.1506\n0.0159\n');

fprintf('按回车继续.\n');
pause;

%% ============= Part 2: Regularization and Accuracies =============
%  Optional Exercise:
%  In this part, you will get to try different values of lambda and 
%  see how regularization affects the decision coundart
%
%  Try the following values of lambda (0, 1, 10, 100).
%
%  How does the decision boundary change when you vary lambda? How does
%  the training set accuracy vary?
%

% Initialize fitting parameters
initial_theta = zeros(size(X, 2), 1);

% Set regularization parameter lambda to 1 (you should vary this)
lambda = 1;

% Set Options
options = optimset('GradObj', 'on', 'MaxIter', 400);

% Optimize
[theta, J, exit_flag] = ...
	fminunc(@(t)(costFunctionReg(t, X, y, lambda)), initial_theta, options);

% Plot Boundary
plotDecisionBoundary(theta, X, y);
hold on;
title(sprintf('lambda = %g', lambda))

% Labels and Legend
xlabel('Microchip Test 1')
ylabel('Microchip Test 2')

legend('y = 1', 'y = 0', 'Decision boundary')
hold off;

% Compute accuracy on our training set
p = predict(theta, X);

fprintf('训练精度: %f\n', mean(double(p == y)) * 100);
fprintf('期待精度(λ = 1): 83.1\n');

