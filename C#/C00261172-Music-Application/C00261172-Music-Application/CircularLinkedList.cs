using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application.DataStructure
{
    internal class CircularLinkedList<T>
    {
        public void insert(T data)
        {
            DoubleLinkedNode<T> node = new(data, this.head, this.tail);
            if (this.tail != null)
            {
                this.tail.Next = node;
            }
            if (this.head == null)
            {
                this.head = node;
            }
            this.tail = node;
            this.count++;
        }
        public DoubleLinkedNode<T>? head { get; private set; }
        public DoubleLinkedNode<T>? tail { get; private set; }
        public int count { get; private set; }
    }
}
