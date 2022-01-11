d:\Gst_Feature_Branch\gcmp_gst\source\GcmpSdk\Db\GcmpModel\CopyPaste\CopyOperator.cpp 184

```cpp
std::set_difference(copyStrategyReporter.GetIdsToCopy().begin(), copyStrategyReporter.GetIdsToCopy().end(), allIdsToCopy.begin(), allIdsToCopy.end(), std::inserter(notVisited, notVisited.end()));
```

set_difference

std::inerter

```cpp
        std::unordered_map<ElementId, ElementId, ElementIdHash> oldToNewMap(allIdsToCopy.size() * 2);
   

struct ElementIdHash
    {
        std::size_t operator()(const ElementId& key) const
        {
            return std::hash<Int64>()(key.AsInt64());
        }
    };
```

