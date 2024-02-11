#include <iostream>
#include <vector>

class MemoryPool
{
    private:
        std::vector<char *> memoryBlocks;
        std::vector<bool> isBlockAllocated;
        size_t blockSize;
        size_t poolSize;
        size_t numBlocks;

    public:
        MemoryPool(size_t blockSize, size_t poolSize) : blockSize(blockSize), poolSize(poolSize)
        {
            numBlocks = poolSize / blockSize;
            isBlockAllocated.resize(numBlocks, false);

            // 分配内存块
            for (size_t i = 0; i < numBlocks; i++)
            {
                char *block = new char[blockSize];
                memoryBlocks.push_back(block);
            }
        }

    ~MemoryPool()
    {
        // 释放内存块
        for (char *block : memoryBlocks)
        {
            delete[] block;
        }
    }

    void *allocate()
    {
        // 查找未分配的内存块
        for (size_t i = 0; i < numBlocks; i++)
        {
            if (!isBlockAllocated[i])
            {
                isBlockAllocated[i] = true;
                return memoryBlocks[i];
            }
        }
        return nullptr; // 没有可用内存块
    }

    void deallocate(void *block)
    {
        // 查找内存块的索引
        for (size_t i = 0; i < numBlocks; i++)
        {
            if (memoryBlocks[i] == block)
            {
                isBlockAllocated[i] = false;
                break;
            }
        }
    }
};

int main()
{
    while (true)
    {
        // 创建内存池，每个内存块大小为100字节，总共有50个内存块
        MemoryPool memoryPool(100, 5000);

        // 分配内存
        char *block1 = static_cast<char *>(memoryPool.allocate());
        char *block2 = static_cast<char *>(memoryPool.allocate());

        if (block1 && block2)
        {
            //std::cout << "成功分配内存块" << std::endl;
        }
        else
        {
            //std::cout << "无法分配内存块" << std::endl;
        }

        // 释放内存
        memoryPool.deallocate(block1);
        memoryPool.deallocate(block2);
    }

    return 0;
}
