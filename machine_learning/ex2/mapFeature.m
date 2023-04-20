function out = mapFeature(X1, X2)
% MAPFEATURE Feature mapping function to polynomial features
%
%   MAPFEATURE(X1, X2) maps the two input features
%   to quadratic features used in the regularization exercise.
%
%   Returns a new feature array with more features, comprising of 
%   X1, X2, X1.^2, X2.^2, X1*X2, X1*X2.^2, etc..
%
%   Inputs X1, X2 must be the same size
%

degree = 6;

row = length(X1);

% 1 + 2(x1+x2) + 3(x1^2+x1x2+x2^2) + 4 + 5 + ...
col = (degree + 2) * (degree + 1) / 2;

out = ones(row, col);

c = 2;
for i = 1:degree
   for j = 0:i
      out(:, c) = (X1.^(i-j)).*(X2.^j);
      c = c + 1;
    end
end

end