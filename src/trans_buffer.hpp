#ifndef _TS_BUFFER_HEADER
#define _TS_BUFFER_HEADER

#include <cstddef>
#include <cstring>

namespace transfer {

    /* 
    *  This buffer is a fixed memory buffer that reads and writes in a ring and does not change in size. 
    *  Failure is returned if there is not enough space in the buffer while writing the contents. 
    *  The contents read must be copied out when reading the contents.
    */
    template<typename T>
    class data_buffer_v1 {
    public:
        data_buffer_v1():
        m_pData(nullptr),
        m_nSize(0),
        m_readcur(0),
        m_writecur(0)
        {
        }
        ~data_buffer_v1() {
            freeMem();
        }
    public:
        // alloc memory
        bool allocMem(std::size_t nSize = 4096) {
            if (nSize < 2) {
                return false;
            }
            m_pData = new T[nSize];
            std::memset(m_pData, 0x0, sizeof(T) * nSize);
            if (!m_pData) {
                return false;
            }
            m_nSize = nSize;
            m_realSize = nSize;
            reset();
            return true;
        }
        // free memory
        void freeMem() {
            delete [] m_pData;
            m_pData = nullptr;
        }
        // wirte data
        bool write(const T* pData, std::size_t nSize) {

            // check remain space
            std::size_t ndiff = 0;
            if (m_bLead) {
                ndiff = m_readcur - m_writecur;
                if (ndiff < nSize) {
                    return false;
                }
            } else {
                ndiff = m_nSize - m_writecur;
                if (ndiff < nSize) {
                    if (m_readcur > nSize) {
                        m_readcur = m_writecur;
                        m_bLead = true;
                        m_writecur = 0;
                    } else {
                        return false;
                    }
                } 
            }
            std::memcpy(m_pData + m_writecur * sizeof(T), pData, nSize);
            m_writecur += nSize;

            if (m_writecur >= m_readcur) {
                m_readcur = m_writecur;
            }

            return true;
        }
        // read data
        std::size_t read(T* pData, int nSize) {

            std::size_t readLen = 0;
            std::size_t max = m_realSize < m_nSize ? m_realSize : m_nSize;
            std::size_t contentLen = max - m_readcur;

            if (contentLen <= nSize) {
                readLen = contentLen;
                m_readcur = 0;
                m_bLead = false;
            } else {
                readLen = contentLen;
            }

            if (readLen > 0) {
                std::memcpy(pData, m_pData + m_readcur * sizeof(T), readLen);
            }
            return readLen;
        }
    private:
        // reset cursor
        void reset() {
            m_writecur = 0;
            m_readcur = 0;
            m_bLead = false;
        }
    private:
        T*              m_pData;
        std::size_t     m_nSize;
        std::size_t     m_writecur;     // current write position
        std::size_t     m_readcur;      // current read position
        std::size_t     m_realSize;     // The maximum position actually written to
        bool            m_bLead;        // Whether m_writecur has exceeded B m_readcur one lap (One lap at most)
    };


    /*  This buffer is a variable-length buffer, adding data to the buffer triggers user callbacks, 
    *   and the user can reset the cursor after parsing the contents.
    */
    template<typename T>
    class data_buffer_v2 {
    public:
        data_buffer_v2()
        {

        }
    private:
        
    };
}

#endif