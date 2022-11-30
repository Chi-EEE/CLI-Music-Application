using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application
{
    internal class DoubleLinkedNode<T>
    {
        public DoubleLinkedNode(T data, DoubleLinkedNode<T>? prev, DoubleLinkedNode<T>? next) { 
            this.data = data;
            this.prev = prev;
            this.next = next;
        }
        public T data { get; }
        public DoubleLinkedNode<T>? prev;
        public DoubleLinkedNode<T>? next;
    }
}
