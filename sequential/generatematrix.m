function A = generatematrix(n)
% GENERATEMATRIX : Test matrix for power method
%
% A = generatematrix(n);   
%
% This routine generates an n-by-n matrix whose spectral radius is n.
%
% John R. Gilbert    11 Jan 2010

% A shorter way to do this in Matlab would be
% A = tril( (1:n)' * ones(1,n) );

A = zeros(n,n);
for i = 1:n
    for j = 1:i
        A(i,j) = i;
    end;
end;