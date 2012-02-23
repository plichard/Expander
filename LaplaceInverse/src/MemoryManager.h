/*
 * MemoryManager.h
 *
 *  Created on: Feb 23, 2012
 *      Author: eagle2com
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

#include <cstdlib>
#include <cstdio>

template <class T>
class MemoryManager {
public:
	MemoryManager(unsigned int size)
	{
		m_mem_block = new T[size];
		m_free_blocks = new unsigned int[size];
		m_free_count = size;
		m_size = size;
		for(unsigned int i = 0; i < size; i++)
		{
			m_free_blocks[i] = size-i-1; //we want to start taking free space from the end
		}


	}
	~MemoryManager()
	{
		printf("Terminating memory manager, check for seg faults =)\n");
		delete[] m_mem_block;
		delete[] m_free_blocks;
	}

	T* New(void) //TODO make it possible to allocate several blocks at once
	{
		if(m_free_count == 0)
			return NULL;

		printf("Allocating block %d\n", m_free_blocks[m_free_count-1]);
		return &m_mem_block[m_free_blocks[m_free_count-- -1]];
	}

	void Free(T* p)
	{
		m_free_blocks[m_free_count++] = p-m_mem_block;
		printf("Freeing block %d\n",p-m_mem_block);
		p = NULL;
	}

private:
	T* m_mem_block;
	unsigned int* m_free_blocks;
	unsigned int m_free_count;
	unsigned int m_size;
};

#endif /* MEMORYMANAGER_H_ */
