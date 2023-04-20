%% Machine Learning Online Class - Exercise 2: Logistic Regression
%
%  Instructions
%  ------------
% 
%  This file contains code that helps you get started on the logistic
%  regression exercise. You will need to complete the following functions 
%  in this exericse:
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
%  The first two columns contains the exam scores and the third column
%  contains the label.

data = load('ex2data1.txt');
X = data(:, [1, 2]); y = data(:, 3);

%% ==================== Part 1: Plotting ====================
%  We start the exercise by first plotting the data to understand the 
%  the problem we are working with.

plotData(X, y);

% Put some labels 
hold on;
% Labels and Legend
xlabel('Exam 1 score');
ylabel('Exam 2 score');

% Specified in plot order
legend('录取', '不录取');
hold off;

fprintf('\n按回车继续.\n');
pause;


%% ============ Part 2: Compute Cost and Gradient ============
%  In this part of the exercise, you will implement the cost and gradient
%  for logistic regression. You neeed to complete the code in 
%  costFunction.m

%  Setup the data matrix appropriately, and add ones for the intercept term
[m, n] = size(X);

% Add intercept term to x and X_test
X = [ones(m, 1) X];

% X = [
%   1 34.62365962451697 78.0246928153624
%   1 30.28671076822607 43.89499752400101
%   ...
% ]

% Initialize fitting parameters
initial_theta = zeros(n + 1, 1);
% initial_theta = [
%    0
%    0
%    0
% ]

% Compute and display initial cost and gradient
[cost, grad] = costFunction(initial_theta, X, y);

fprintf('初始拟合参数 theta 为: %f\n', cost);
fprintf('期待值(大约): 0.693\n');

fprintf('initial_theta 处的梯度:\n');
fprintf('%f \n', grad);
fprintf('期待梯度(大约):\n-0.1000\n-12.0092\n-11.2628\n');

% Compute and display cost and gradient with non-zero theta
test_theta = [-24; 0.2; 0.2];
[cost, grad] = costFunction(test_theta, X, y);

fprintf('\n使用测试 theta 时的代价: %f\n', cost);
fprintf('期待代价(大约): 0.218\n');

fprintf('测试 theta 处的梯度: \n');
fprintf('%f \n', grad);
fprintf('期待梯度(大约):\n0.043\n2.566\n2.647\n');

fprintf('\n按回车继续.\n');
pause;


%% ============= Part 3: Optimizing using fminunc  =============
%  In this exercise, you will use a built-in function (fminunc) to find the
%  optimal parameters theta.

%  Set options for fminunc
options = optimset('GradObj', 'on', 'MaxIter', 400);

%  Run fminunc to obtain the optimal theta
%  This function will return theta and the cost 
[theta, cost] = ...
	fminunc(@(t)(costFunction(t, X, y)), initial_theta, options);

% Print theta to screen
fprintf('使用 fminunc 计算的代价: %f\n', cost);
fprintf('期待的代价(大约): 0.203\n');

fprintf('theta: \n');
fprintf('%f \n', theta);
fprintf('期待的 theta (大约):\n-25.161\n0.206\n0.201\n');

% Plot Boundary
plotDecisionBoundary(theta, X, y);

% Put some labels 
hold on;
% Labels and Legend
xlabel('Exam 1 score')
ylabel('Exam 2 score')

% Specified in plot order
legend('录取', '不录取')
hold off;

fprintf('\n按回车继续.\n');
pause;

%% ============== Part 4: Predict and Accuracies ==============
%  After learning the parameters, you'll like to use it to predict the outcomes
%  on unseen data. In this part, you will use the logistic regression model
%  to predict the probability that a student with score 45 on exam 1 and 
%  score 85 on exam 2 will be admitted.
%
%  Furthermore, you will compute the training and test set accuracies of 
%  our model.
%
%  Your task is to complete the code in predict.m

%  Predict probability for a student with score 45 on exam 1 
%  and score 85 on exam 2 

prob = sigmoid([1 45 85] * theta);
fprintf(['考试一得分 45 以及考试二得分 85 的学生录取率为: %f\n'], prob);

fprintf('期待值: 0.775 +/- 0.002\n\n');

% Compute accuracy on our training set
p = predict(theta, X);

fprintf('训练精度: %f\n', mean(double(p == y)) * 100);
fprintf('期待精度(大约): 89.0\n');
fprintf('\n');


