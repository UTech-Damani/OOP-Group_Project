# Included tests

Run these from the `main` directory:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic tests/core_workflow_test.cpp -o core_workflow_test
./core_workflow_test

g++ -std=c++11 -Wall -Wextra -pedantic tests/business_rules_test.cpp -o business_rules_test
./business_rules_test
```

The tests cover fixture creation, official assignment, result processing,
league-point calculations, serialization, completion validation, scheduling
conflicts, negative scores, stadium capacity, and payment/change handling.
