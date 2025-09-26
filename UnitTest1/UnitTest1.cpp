#include "pch.h"
#include "../Тестирование и Unit-тесты/extended_array.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(ExtArrayTest)
    {
    public:

        TEST_METHOD(EmptyArrayMean)
        {
            ExtArray<int> arr;
            Assert::AreEqual(0.0, arr.mean());
        }

        TEST_METHOD(EmptyArrayMedian)
        {
            ExtArray<int> arr;
            Assert::AreEqual(0.0, arr.median());
        }

        TEST_METHOD(EmptyArrayMode)
        {
            ExtArray<int> arr;
            auto result = arr.mode();
            Assert::AreEqual(0, result.first);
            Assert::AreEqual(0, result.second);
        }
    };
}

