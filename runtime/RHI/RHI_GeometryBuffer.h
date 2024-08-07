/*
Copyright(c) 2016-2024 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES =====================
#include "../Core/SpartanObject.h"
//================================

namespace Spartan
{
    enum class RHI_Buffer_Type
    {
        Vertex,
        Instance,
        Index,
        Max
    };

    class RHI_GeometryBuffer : public SpartanObject
    {
    public:
        RHI_GeometryBuffer() = default;
        RHI_GeometryBuffer(const RHI_Buffer_Type type, const bool is_mappable, const char* name)
        {
            m_type        = type;
            m_is_mappable = is_mappable;
            m_object_name = name;
        }
        ~RHI_GeometryBuffer();

        template<typename T>
        void Create(const std::vector<T>& data)
        {
            m_stride        = sizeof(T);
            m_element_count = static_cast<uint32_t>(data.size());
            m_object_size   = static_cast<uint64_t>(m_stride * m_element_count);

            RHI_CreateResource(static_cast<const void*>(data.data()));
        }

        template<typename T>
        void Create(const T* indices, const uint32_t index_count)
        {
            m_stride        = sizeof(T);
            m_element_count = index_count;
            m_object_size   = static_cast<uint64_t>(m_stride * m_element_count);

            RHI_CreateResource(static_cast<const void*>(indices));
        }

        template<typename T>
        void CreateDynamic(const uint32_t index_count)
        {
            m_stride        = sizeof(T);
            m_element_count = index_count;
            m_object_size   = static_cast<uint64_t>(m_stride * m_element_count);

            RHI_CreateResource(nullptr);
        }

        void* GetMappedData() const      { return m_mapped_data; }
        void* GetRhiResource() const     { return m_rhi_resource; }
        uint32_t GetElementCount() const { return m_element_count; }
        uint32_t GetStride() const       { return m_stride; }

    private:
        RHI_Buffer_Type m_type   = RHI_Buffer_Type::Max;
        void* m_mapped_data      = nullptr;
        bool m_is_mappable       = false;
        uint32_t m_stride        = 0;
        uint32_t m_element_count = 0;

        // rhi
        void RHI_CreateResource(const void* indices);
        void* m_rhi_resource = nullptr;
    };
}
