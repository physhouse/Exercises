function [C, sigma] = dataset3Params(X, y, Xval, yval)
%EX6PARAMS returns your choice of C and sigma for Part 3 of the exercise
%where you select the optimal (C, sigma) learning parameters to use for SVM
%with RBF kernel
%   [C, sigma] = EX6PARAMS(X, y, Xval, yval) returns your choice of C and 
%   sigma. You should complete this function to return the optimal C and 
%   sigma based on a cross-validation set.
%

% You need to return the following variables correctly.
C = 1;
sigma = 0.3;

% ====================== YOUR CODE HERE ======================
% Instructions: Fill in this function to return the optimal C and sigma
%               learning parameters found using the cross validation set.
%               You can use svmPredict to predict the labels on the cross
%               validation set. For example, 
%                   predictions = svmPredict(model, Xval);
%               will return the predictions on the cross validation set.
%
%  Note: You can compute the prediction error using 
%        mean(double(predictions ~= yval))
%
C_lib = [0.01 0.03 0.10 0.30 1.00 3.00 10.00 30.0];
S_lib = [0.01 0.03 0.10 0.30 1.00 3.00 10.00 30.0];
e_min = 10000.0;
for i=1:1:length(C_lib)
    for j=1:1:length(S_lib)
        model= svmTrain(X, y, C_lib(i), @(x1, x2) gaussianKernel(x1, x2, S_lib(j))); 
        predictions = svmPredict(model, Xval);
        error = mean(double(predictions ~= yval));
        if error < e_min
            e_min = error;
            C = C_lib(i);
            sigma = S_lib(j);
        end
    end
end

% =========================================================================

end
