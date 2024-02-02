n = 1503;
estimated_probability = 0;
expected_weight = 0;
standard_deviation = 0;
weights = zeros(n, 1);
ship_lengths = [50 40 25];
weight_a = [60 100 120];
weight_l = [0.1 0.05 0.02];
u = 0;
tmp = 0;
f = 0;
current_length = 0;
current_weight = 0;
ndex = 10000000;
for sample_idx = 1:n
  for ship_idx = 1:3
  current_length = ship_lengths(ship_idx);
  u = rand;
  tmp = 0;
  f = exp(-current_length);
    for i = 1:ndex
      x = x + 1;
      f = f + exp(-current_length) * current_length^x / gamma(x + 1);
      if (u <= f)
        break;
      endif
    endfor
    for i = 1:tmp
      current_weight = sum(-1 / weight_l(ship_idx) * log(rand(weight_a(ship_idx), 1)));
      weights(sample_idx) = weights(sample_idx) + current_weight;
    endfor
  endfor
endfor
estimated_probability = mean(weights > 300000);
expected_weight = mean(weights);
standard_deviation = std(weights);
fprintf("Weight: %f\n", expected_weight);
fprintf("Std %f\n", standard_deviation);
fprintf("Probability %f\n", estimated_probability);

