cxx_test(
   TARGET euclidean_vector_test1
   FILENAME "euclidean_vector_test1.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)
cxx_test(
   TARGET constructor_tests
   FILENAME "constructor_tests.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)
cxx_test(
   TARGET operator_overloading_tests
   FILENAME "operator_overloading_tests.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)
cxx_test(
   TARGET member_functions_test
   FILENAME "member_functions_test.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)
cxx_test(
   TARGET friends_test
   FILENAME "friends_test.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)
cxx_test(
   TARGET utility_tests
   FILENAME "utility_tests.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)
