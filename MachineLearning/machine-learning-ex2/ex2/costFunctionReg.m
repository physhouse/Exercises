function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

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

z = X * theta;
lgh_theta = log(sigmoid(z));
lghminus_theta = log(1 - sigmoid(z));
J = y' * lgh_theta + (1-y)' * lghminus_theta;
J = -J / m;

reg_theta = theta(2:end);
J = J + 0.5 * (lambda / m) * (reg_theta' * reg_theta);

dev = sigmoid(z) - y;

grad(1) = (dev' * X(:,1))/m;
for i=2:1:size(theta)
    sum = (dev' * X(:,i));
    grad(i) = sum / m + (lambda / m) * theta(i);
end


% =============================================================

end