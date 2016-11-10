function [J, grad] = costFunction(theta, X, y)
%COSTFUNCTION Compute cost and gradient for logistic regression
%   J = COSTFUNCTION(theta, X, y) computes the cost of using theta as the
%   parameter for logistic regression and the gradient of the cost
%   w.r.t. to the parameters.

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
grad = zeros(size(theta));

% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta
%
% Note: grad should have the same dimensions as theta
%

z = X * theta;
lgh_theta = log(sigmoid(z));
lghminus_theta = log(1 - sigmoid(z));
J = y' * lgh_theta + (1-y)' * lghminus_theta;
J = -J / m;

dev = sigmoid(z) - y;

for i=1:1:size(theta)
    sum = (dev' * X(:,i));
    grad(i) = sum / m;
end

% =============================================================

end
