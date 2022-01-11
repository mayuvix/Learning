#### 空事务

空事务中的空指的是最终的数据状态。发生过增删改的也可能为空，比如新增了一个对象，然后又修改，最后又删除了该对象，该事务为空。

#### 平台对空事务的处理

平台现在对空事务会记录下来，undo/redo时也会执行。

平台分别提供了两种处理undo/redo的接口：

##### 1、单步执行undo/redo

这种方式会根据undo/redo列表的执行顺序单步执行，其中包括空事务也是单步执行。平台现在默认的逻辑就是单步执行。

单步执行undo/redo的接口为：

```cpp
 /// \brief 撤消上一步操作
/// \param pDocument 文档指针
/// \param pUndoConfirm 请用户确认执行undo
/// \return  true表示撤消成功，false表示撤消失败
static bool Undo(
    IDocument* pDocument, 
    IUndoConfirm * pUndoConfirm = nullptr
);

/// \brief 重做一步操作
/// \param pDocument 文档指针
/// \return  true表示重做成功，false表示重做失败
static bool Redo(IDocument* pDocument);
```



##### 2、根据undo/redo的Id执行到指定的某一步

  平台提供一系列接口，用户可根据实际需求执行到某一步，接口如下（接口定义在UndoRedoUtils.h中）：

（1）平台提供获取Undo/Redo的UndoRedoEntityBrief的列表的接口，可让用户获得Undo/Redo的一些基本信息，包括Id，Name，IsEmpty

```cpp
/// \brief 按撤消时执行顺序获取所有可撤消操作的摘要信息列表，摘要信息包括：Name，Id，IsEmpty
/// \param pDocument 文档指针
/// \return std::vector<UndoRedoEntityBrief> 所有可撤消操作的摘要信息列表，列表的头部是最近的一次可撤消操作的摘要信息
static std::vector<UndoRedoEntityBrief> GetUndoEntityBriefs(const IDocument* pDocument);


/// \brief 按重做时执行顺序获取所有可重做操作的摘要信息列表，摘要信息包括：Name，Id，IsEmpty
/// \param pDocument 文档指针
/// \return std::vector<UndoRedoEntityBrief> 所有可重做操作的摘要信息列表，列表的头部是最近的一次可重做操作的摘要信息
static std::vector<UndoRedoEntityBrief> GetRedoEntityBriefs(const IDocument* pDocument);
```

（3）平台提供根据undo/redo的Id判断该事物是否为空的接口

```cpp
 /// \brief 判断undo的数据实体是否为空
/// \param pDocument 文档指针
/// \param undoId undo的Id,这里的undoId不能任意给，从GetUndoEntityBriefs(const IDocument* pDocument)取值,否则返回false
/// \return  bool false表示不为空，true表示为空
static bool IsUndoEmpty(const IDocument* pDocument, int32_t undoId);


/// \brief 判断redo的数据实体是否为空
/// \param pDocument 文档指针
/// \param redoId redo的Id，这里的undoId不能任意给，从 GetRedoEntityBriefs(const IDocument* pDocument)取值,否则返回false
/// \return  bool false表示不为空，true表示为空
static bool IsRedoEmpty(const IDocument* pDocument, int32_t redoId);
```

（2）平台提供获取下一个非空的Undo/Redo的Id的接口

```cpp
/// \brief 获取下一个非空的undo Id
/// \param pDocument 文档指针
/// \param [out] resultOfGetNextNotEmptyUndoRedoId
/// \return int32_t 返回下一个非空undo Id，如果容器为空或者每一个undo都是空返回-1
/// \note 这是一个便利函数，可以通过GetUndoEntityBriefs(const IDocument* pDocument)实现
static int32_t GetNextNotEmptyUndoId(const IDocument* pDocument, ResultOfGetNextNotEmptyUndoRedoId & resultOfGetNextNotEmptyUndoRedoId);


/// \brief 获取下一个非空的redo Id
/// \param pDocument 文档指针
/// \param [out] resultOfGetNextNotEmptyUndoRedoId
/// \return int32_t 返回下一个非空redo Id，如果容器为空或者每一个redo都是空返回-1
/// \note 这是一个便利函数，可以通过GetRedoEntityBriefs(const IDocument* pDocument)实现
static int32_t GetNextNotEmptyRedoId(const IDocument* pDocument, ResultOfGetNextNotEmptyUndoRedoId & resultOfGetNextNotEmptyUndoRedoId);
```

（3）平台提供根据Undo/Redo的Id，可以Undo/Redo到某一步的接口

```cpp
/// \brief 撤消操作到给定的undo Id
/// \param pDocument 文档指针
/// \param undoId 期望执行到的undo的Id
/// \param pUndoConfirm 请用户确认执行undo
/// \return  true表示撤消成功，false表示撤消失败，失败的情况包括pDocument为空，或者undoId不合法，或者中间任意一步失败
static bool Undo(
    IDocument* pDocument,
    int32_t undoId,
    IUndoConfirm * pUndoConfirm = nullptr
);


/// \brief 重做操作到给定的redo Id
/// \param pDocument 文档指针
/// \param redoId 期望执行到的redo的Id
/// \return  true表示重做成功，false表示重做失败，失败的情况包括pDocument为空，或者redoId不合法，或者中间任意一步失败
static bool Redo(
    IDocument* pDocument,
    int32_t redoId
);
```

（4）针对该undo/redo方式，平台提供了测试命令：TestCmdUndoRedo.cpp。命令入口：[内部-试验功能] -> [空事务]、[测试undo]、[测试redo]。API使用范例如下：

测试undocmd

```cpp
//
gcmp::OwnerPtr<IAction> TestCmdUndo::ExecuteCommand(const gcmp::CommandParameters& cmdParams)
{
    ……
    // DB层撤消操作
    TestUndoConfirm undoConfirm;

    //根据指定的undo的ID撤销，撤销到下一个非空的事务
    GetNextEmptyUndoRedoIdResult result;
    int32_t nextNotEmptyUndoId = UndoRedoUtils::GetNextNotEmptyUndoId(pDoc, result);     根据返回值判断
    if (nextNotEmptyUndoId != -1)
    {
        UndoRedoUtils::Undo(pDoc, nextNotEmptyUndoId, &undoConfirm);
    }
    else
    {
        if (ResultOfGetNextNotEmptyUndoRedoId::AllUndoRedoEntityAreEmpty == result)
        {
            // 有两种方式，一是啥都不做，二是将空的UndoEntity也Undo掉。
            // 建议将空的也Undo掉。两个好处：1）照常发出Undo/Redo相关事件，2）不会在Undo/Redo容器里积累空事务
            while (!(UndoRedoUtils::GetUndoEntityBriefs(pDoc).empty()))
            {
                UndoRedoUtils::Undo(pDoc, &undoConfirm);
            }
        }
        else if (ResultOfGetNextNotEmptyUndoRedoId::UndoOrRedoContainerIsEmpty == result)
        {
            DBG_WARN_AND_RETURN_NULLPTR_UNLESS(false, L"不应该到这里，前面调用CanUndo应该能判断出", L"luoxj", L"2020-08-13");
        }
        else
        {
            DBG_WARN_AND_RETURN_NULLPTR_UNLESS(false, L"不支持ResultOfGetNextNotEmptyUndoRedoId的枚举类型", L"luoxj", L"2020-08-13");
        }
    }

	……

    return nullptr;
}
```



测试redocmd

```cpp
gcmp::OwnerPtr<IAction> TestCmdRedo::ExecuteCommand(const gcmp::CommandParameters& cmdParams)
{
    ……

    std::vector<std::wstring> redoName = UndoRedoUtils::GetRedoNames(pDoc);
    DBG_WARN_AND_RETURN_NULLPTR_UNLESS(!redoName.empty(), L"Redo名字列表为空？", L"陈鹏宇", L"2020/03/25");

    //根据指定的redo的ID撤销，重做到下一个非空的事务
    GetNextEmptyUndoRedoIdResult result;
    int32_t nextNotEmptyRedoId = UndoRedoUtils::GetNextNotEmptyRedoId(pDoc, result);
     if (nextNotEmptyRedoId != -1)
    {
        UndoRedoUtils::Redo(pDoc, nextNotEmptyRedoId);
    }
    else
    {
        if (ResultOfGetNextNotEmptyUndoRedoId::AllUndoRedoEntityAreEmpty == result)
        {
            // 有两种方式，一是啥都不做，二是将空的UndoEntity也Redo掉。
            // 建议将空的也Redo掉。两个好处：1）照常发出Undo/Redo相关事件，2）不会在Undo/Redo容器里积累空事务
            while (!(UndoRedoUtils::GetRedoEntityBriefs(pDoc).empty()))
            {
                UndoRedoUtils::Redo(pDoc);
            }
        }
        else if (ResultOfGetNextNotEmptyUndoRedoId::UndoOrRedoContainerIsEmpty == result)
        {
            DBG_WARN_AND_RETURN_NULLPTR_UNLESS(false, L"不应该到这里，前面调用CanRedo应该能判断出", L"luoxj", L"2020-08-13");
        }
        else
        {
            DBG_WARN_AND_RETURN_NULLPTR_UNLESS(false, L"不支持ResultOfGetNextNotEmptyUndoRedoId的枚举类型", L"luoxj", L"2020-08-13");
        }
    }
    
  ……

    return nullptr;
}
```



**说明：新提供的API和现有的API同时存在，由产品根据实际需求选用。平台原来undo/redo入口保持不变，仍然是单步执行undo/redo的逻辑。对于新加的API提供测试命令， 新增测试的undo/redo入口：[内部-试验功能] -> [空事务]、[测试undo]、[测试redo]。**