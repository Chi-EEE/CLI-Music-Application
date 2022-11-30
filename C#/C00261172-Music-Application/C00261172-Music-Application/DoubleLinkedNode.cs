using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application.DataStructure
{
    internal class DoubleLinkedNode<T>
    {
        public DoubleLinkedNode(T data, DoubleLinkedNode<T>? prev, DoubleLinkedNode<T>? next)
        {
            this.Data = data;
            if (prev == null)
            {
                this.Prev = this;
            }
            else
            {
                this.Prev = prev;
            }
            if (next == null)
            {
                this.Next = this;
            }
            else
            {
                this.Next = next;
            }
        }
        public T Data { get; }
        public DoubleLinkedNode<T> Prev;
        public DoubleLinkedNode<T> Next;
    }
}
