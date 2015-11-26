
// Tiny Container Template Library for Arduino
// Copyright (C) 2015 S.Fuchita (@soramimi_jp)

#ifndef TinyContainer_h_
#define TinyContainer_h_

#include <arduino.h>
#include <stdlib.h>
#include <new>

namespace tiny {
	template <typename T> class vector {
	private:
		size_t capacity;
		size_t count;
		T *array;
	public:
		vector()
			: capacity(0)
			, count(0)
			, array(0)
		{
		}
		vector(vector const &r)
			: capacity(0)
			, count(0)
			, array(0)
		{
			reserve(r.size());
			for (const_iterator it = r.begin(); it != r.end(); it++) {
				push_back(*it);
			}
		}
		~vector()
		{
			clear();
			delete[] (char *)array;
		}
		void operator = (vector const &r)
		{
			clear();
			reserve(r.size());
			for (const_iterator it = r.begin(); it != r.end(); it++) {
				push_back(*it);
			}
		}
		class const_iterator;
		class iterator {
			friend vector;
			friend const_iterator;
		private:
			T *ptr;
			T *end;
			int compare(iterator const &r) const
			{
				return ptr - r.ptr;
			}
			bool isnull() const
			{
				return !ptr || ptr == end;
			}
		public:
			iterator(T *p, T *end = 0)
				: ptr(p)
				, end(end)
			{
			}
			bool operator == (iterator it) const
			{
				if (isnull() && it.isnull()) return true;
				return compare(it) == 0;
			}
			bool operator != (iterator it) const
			{
				return !operator == (it);
			}
			void operator ++ ()
			{
				if (!isnull()) ptr++;
			}
			void operator ++ (int)
			{
				if (!isnull()) ptr++;
			}
			T &operator * ()
			{
				return *ptr;
			}
			T *operator -> ()
			{
				return ptr;
			}
			iterator operator + (size_t n) const
			{
				return isnull() ? iterator(end, end) : iterator(ptr + n, end);
			}
			iterator operator - (size_t n) const
			{
				return isnull() ? iterator(end, end) : iterator(ptr - n, end);
			}
			bool operator < (iterator const &it) const
			{
				return compare(it) < 0;
			}
			bool operator > (iterator const &it) const
			{
				return compare(it) > 0;
			}
			bool operator <= (iterator const &it) const
			{
				return compare(it) <= 0;
			}
			bool operator >= (iterator const &it) const
			{
				return compare(it) >= 0;
			}
			size_t operator - (iterator const &it) const
			{
				if (!ptr || !it.ptr) return 0;
				return ptr - it.ptr;
			}
		};
		class const_iterator {
			friend vector;
		private:
			T const *ptr;
			T const *end;
			int compare(const_iterator const &r) const
			{
				return ptr - r.ptr;
			}
			bool isnull() const
			{
				return !ptr || ptr == end;
			}
		public:
			const_iterator(T const *p, T const *end = 0)
				: ptr(p)
				, end(end)
			{
			}
			const_iterator(iterator const &it)
				: ptr(it.ptr)
				, end(it.end)
			{
			}
			bool operator == (const_iterator it) const
			{
				if (isnull() && it.isnull()) return true;
				return compare(it) == 0;
			}
			bool operator != (const_iterator it) const
			{
				return !operator == (it);
			}
			void operator ++ ()
			{
				if (!isnull()) ptr++;
			}
			void operator ++ (int)
			{
				if (!isnull()) ptr++;
			}
			T const &operator * () const
			{
				return *ptr;
			}
			T const *operator -> () const
			{
				return ptr;
			}
			iterator operator + (size_t n) const
			{
				return isnull() ? const_iterator(end, end) : const_iterator(ptr + n, end);
			}
			iterator operator - (size_t n) const
			{
				return isnull() ? const_iterator(end, end) : const_iterator(ptr - n, end);
			}
			bool operator < (const_iterator const &it) const
			{
				return compare(it) < 0;
			}
			bool operator > (const_iterator const &it) const
			{
				return compare(it) > 0;
			}
			bool operator <= (const_iterator const &it) const
			{
				return compare(it) <= 0;
			}
			bool operator >= (const_iterator const &it) const
			{
				return compare(it) >= 0;
			}
			size_t operator - (const_iterator const &it) const
			{
				if (!ptr || !it.ptr) return 0;
				return ptr - it.ptr;
			}
		};
		class reverse_iterator {
			friend vector;
			friend const_iterator;
		private:
			T *ptr;
			T *end;
			int compare(reverse_iterator const &r) const
			{
				return ptr - r.ptr;
			}
			bool isnull() const
			{
				return !ptr || ptr == end;
			}
		public:
			reverse_iterator(T *p, T *end = 0)
				: ptr(p)
				, end(end)
			{
			}
			bool operator == (reverse_iterator it) const
			{
				if (isnull() && it.isnull()) return true;
				return compare(it) == 0;
			}
			bool operator != (reverse_iterator it) const
			{
				return !operator == (it);
			}
			void operator ++ ()
			{
				if (!isnull()) ptr--;
			}
			void operator ++ (int)
			{
				if (!isnull()) ptr--;
			}
			T &operator * ()
			{
				return ptr[-1];
			}
			T *operator -> ()
			{
				return &ptr[-1];
			}
			reverse_iterator operator + (size_t n) const
			{
				return isnull() ? reverse_iterator(end, end) : reverse_iterator(ptr - n, end);
			}
			reverse_iterator operator - (size_t n) const
			{
				return isnull() ? reverse_iterator(end, end) : reverse_iterator(ptr + n, end);
			}
			bool operator < (reverse_iterator const &it) const
			{
				return compare(it) > 0;
			}
			bool operator > (reverse_iterator const &it) const
			{
				return compare(it) < 0;
			}
			bool operator <= (reverse_iterator const &it) const
			{
				return compare(it) >= 0;
			}
			bool operator >= (reverse_iterator const &it) const
			{
				return compare(it) <= 0;
			}
			size_t operator - (reverse_iterator const &it) const
			{
				if (!ptr || !it.ptr) return 0;
				return it.ptr - ptr;
			}
		};
		class const_reverse_iterator {
			friend vector;
			friend const_iterator;
		private:
			T const *ptr;
			T const *end;
			int compare(const_reverse_iterator const &r) const
			{
				return ptr - r.ptr;
			}
			bool isnull() const
			{
				return !ptr || ptr == end;
			}
		public:
			const_reverse_iterator(T *p, T *end = 0)
				: ptr(p)
				, end(end)
			{
			}
			const_reverse_iterator(reverse_iterator const &r)
				: ptr(r.ptr)
				, end(r.end)
			{
			}
			bool operator == (const_reverse_iterator it) const
			{
				if (isnull() && it.isnull()) return true;
				return compare(it) == 0;
			}
			bool operator != (const_reverse_iterator it) const
			{
				return !operator == (it);
			}
			void operator ++ ()
			{
				if (!isnull()) ptr--;
			}
			void operator ++ (int)
			{
				if (!isnull()) ptr--;
			}
			T const &operator * () const
			{
				return ptr[-1];
			}
			T const *operator -> () const
			{
				return &ptr[-1];
			}
			const_reverse_iterator operator + (size_t n) const
			{
				return isnull() ? const_reverse_iterator(end, end) : const_reverse_iterator(ptr - n, end);
			}
			const_reverse_iterator operator - (size_t n) const
			{
				return isnull() ? const_reverse_iterator(end, end) : const_reverse_iterator(ptr + n, end);
			}
			bool operator < (const_reverse_iterator const &it) const
			{
				return compare(it) > 0;
			}
			bool operator > (const_reverse_iterator const &it) const
			{
				return compare(it) < 0;
			}
			bool operator <= (const_reverse_iterator const &it) const
			{
				return compare(it) >= 0;
			}
			bool operator >= (const_reverse_iterator const &it) const
			{
				return compare(it) <= 0;
			}
			size_t operator - (const_reverse_iterator const &it) const
			{
				if (!ptr || !it.ptr) return 0;
				return it.ptr - ptr;
			}
		};
		size_t size() const
		{
			return count;
		}
		void resize(size_t n)
		{
			while (size() < n) push_back(T());
			while (size() > n) pop_back();
		}
		bool empty() const
		{
			return size() == 0;
		}
		void reserve(size_t n)
		{
			if (capacity < n) {
				T *newarr = (T *)new char [sizeof(T) * n];
				for (size_t i = 0; i < count; i++) {
					new(newarr + i) T(array[i]);
					array[i].~T();
				}
				delete[] (char *)array;
				array = newarr;
				capacity = n;
			}
		}
		void clear()
		{
			for (size_t i = 0; i < count; i++) {
				array[i].~T();
			}
			count = 0;
		}
		iterator begin()
		{
			if (array) {
				return iterator(array, array + count);
			} else {
				return iterator(0, 0);
			}
		}
		const_iterator begin() const
		{
			if (array) {
				return const_iterator(array, array + count);
			} else {
				return const_iterator(0, 0);
			}
		}
		reverse_iterator rbegin()
		{
			if (array) {
				return reverse_iterator(array + count, array);
			} else {
				return reverse_iterator(0, 0);
			}
		}
		const_reverse_iterator rbegin() const
		{
			if (array) {
				return const_reverse_iterator(array + count, array);
			} else {
				return const_reverse_iterator(0, 0);
			}
		}
		iterator end()
		{
			if (array) {
				return iterator(array + count, array + count);
			} else {
				return iterator(0, 0);
			}
		}
		const_iterator end() const
		{
			if (array) {
				return const_iterator(array + count, array + count);
			} else {
				return const_iterator(0, 0);
			}
		}
		reverse_iterator rend()
		{
			if (array) {
				return reverse_iterator(array, array);
			} else {
				return reverse_iterator(0, 0);
			}
		}
		const_reverse_iterator rend() const
		{
			if (array) {
				return const_reverse_iterator(array, array);
			} else {
				return const_reverse_iterator(0, 0);
			}
		}
		iterator insert(iterator it, const_iterator b, const_iterator e)
		{
			if (b < e) {
				size_t i;
				if (it == end()) {
					i = count;
				} else {
					i = it.ptr - array;
				}
				size_t next = 0;
				size_t n = e - b;
				if (n > capacity - count) {
					vector newvec;
					newvec.capacity = ((count + n + 7) & ~7) * 2;
					newvec.array = (T *)new char [sizeof(T) * newvec.capacity];
					if (array && i > 0) {
						newvec.insert(newvec.end(), begin(), begin() + i);
					}
					newvec.insert(newvec.end(), b, e);
					next = newvec.size();
					if (array && count - i > 0) {
						newvec.insert(newvec.end(), begin() + i, end());
					}
					clear();
					delete array;
					capacity = newvec.capacity;
					array = newvec.array;
					count = newvec.count;
					newvec.capacity = 0;
					newvec.count = 0;
					newvec.array = 0;
				} else {
					size_t mv = count - i;
					for (size_t j = 0; j < mv; j++) {
						new(array + count + n - j - 1) T(array[count - j - 1]);
						array[count - j - 1].~T();
					}
					for (size_t j = 0; j < n; j++) {
						new(array + i + j) T(b.ptr[j]);
					}
					count += n;
					next = i + n;
				}
				return iterator(array + next, array + count);
			}
			return iterator(0, 0);
		}
		iterator insert(iterator it, T const v)
		{
			T const *p = &v;
			return insert(it, p, p + 1);
		}
		void push_back(T const &t)
		{
			T const *p = &t;
			insert(end(), p, p + 1);
		}
		void pop_back()
		{
			if (count > 0) {
				count--;
				array[count].~T();
			}
		}
		T &operator [] (size_t i)
		{
			return array[i];
		}
		T const &operator [] (size_t i) const
		{
			return array[i];
		}
	};

	template <typename T> class list {
	private:
		struct node_t {
			node_t *next;
			node_t *prev;
			T val;
			node_t(T const &v)
				: val(v)
				, next(0)
				, prev(0)
			{
			}
		};
		node_t *first;
		node_t *last;
		size_t count;
	public:
		list()
			: count(0)
			, first(0)
			, last(0)
		{
		}
		list(list const &r)
			: count(0)
			, first(0)
			, last(0)
		{
			for (const_iterator it = r.begin(); it != r.end(); it++) {
				push_back(*it);
			}
		}
		~list()
		{
			clear();
		}
		void operator = (list const &r)
		{
			clear();
			for (const_iterator it = r.begin(); it != r.end(); it++) {
				push_back(*it);
			}
		}
		size_t size() const
		{
			return count;
		}
		bool empty() const
		{
			return size() == 0;
		}
		void clear()
		{
			while (first) {
				erase(begin());
			}
		}
		class const_iterator;
		class iterator {
			friend class list;
			friend class const_iterator;
		private:
			node_t *node;
		public:
			iterator(node_t *node)
				: node(node)
			{
			}
			bool operator == (iterator const &it) const
			{
				return node == it.node;
			}
			bool operator != (iterator const &it) const
			{
				return !operator == (it);
			}
			void operator ++ ()
			{
				if (node) node = node->next;
			}
			void operator ++ (int)
			{
				if (node) node = node->next;
			}
			void operator -- ()
			{
				if (node) node = node->prev;
			}
			void operator -- (int)
			{
				if (node) node = node->prev;
			}
			iterator operator + (size_t n) const
			{
				iterator it(node);
				while (it.node && n > 0) it++;
				return it;
			}
			iterator operator - (size_t n) const
			{
				iterator it(node);
				while (it.node && n > 0) it--;
				return it;
			}
			T &operator * ()
			{
				return node->val;
			}
			T *operator -> ()
			{
				return &node->val;
			}
		};
		class const_iterator {
		private:
			friend class list;
			node_t const *node;
		public:
			const_iterator(node_t const *node)
				: node(node)
			{
			}
			const_iterator(iterator const &it)
				: node(it.node)
			{
			}
			bool operator == (const_iterator const &it) const
			{
				return node == it.node;
			}
			bool operator != (const_iterator const &it) const
			{
				return !operator == (it);
			}
			void operator ++ ()
			{
				if (node) node = node->next;
			}
			void operator ++ (int)
			{
				if (node) node = node->next;
			}
			void operator -- ()
			{
				if (node) node = node->prev;
			}
			void operator -- (int)
			{
				if (node) node = node->prev;
			}
			const_iterator operator + (size_t n) const
			{
				const_iterator it(node);
				while (it.node && n > 0) it++;
				return it;
			}
			const_iterator operator - (size_t n) const
			{
				const_iterator it(node);
				while (it.node && n > 0) it--;
				return it;
			}
			T const &operator * () const
			{
				return node->val;
			}
			T const *operator -> () const
			{
				return &node->val;
			}
		};
		class reverse_iterator {
			friend class list;
			friend class const_iterator;
		private:
			node_t *node;
		public:
			reverse_iterator(node_t *node)
				: node(node)
			{
			}
			bool operator == (reverse_iterator const &it) const
			{
				return node == it.node;
			}
			bool operator != (reverse_iterator const &it) const
			{
				return !operator == (it);
			}
			void operator ++ ()
			{
				if (node) node = node->prev;
			}
			void operator ++ (int)
			{
				if (node) node = node->prev;
			}
			void operator -- ()
			{
				if (node) node = node->next;
			}
			void operator -- (int)
			{
				if (node) node = node->next;
			}
			reverse_iterator operator + (size_t n) const
			{
				reverse_iterator it(node);
				while (it.node && n > 0) it++;
				return it;
			}
			reverse_iterator operator - (size_t n) const
			{
				reverse_iterator it(node);
				while (it.node && n > 0) it--;
				return it;
			}
			T &operator * ()
			{
				return node->val;
			}
			T *operator -> ()
			{
				return &node->val;
			}
		};
		class const_reverse_iterator {
			friend class list;
			friend class const_iterator;
		private:
			node_t *node;
		public:
			const_reverse_iterator(node_t *node)
				: node(node)
			{
			}
			const_reverse_iterator(reverse_iterator const &r)
				: node(r.node)
			{
			}
			bool operator == (const_reverse_iterator const &it) const
			{
				return node == it.node;
			}
			bool operator != (const_reverse_iterator const &it) const
			{
				return !operator == (it);
			}
			void operator ++ ()
			{
				if (node) node = node->prev;
			}
			void operator ++ (int)
			{
				if (node) node = node->prev;
			}
			void operator -- ()
			{
				if (node) node = node->next;
			}
			void operator -- (int)
			{
				if (node) node = node->next;
			}
			const_reverse_iterator operator + (size_t n) const
			{
				const_reverse_iterator it(node);
				while (it.node && n > 0) it++;
				return it;
			}
			const_reverse_iterator operator - (size_t n) const
			{
				const_reverse_iterator it(node);
				while (it.node && n > 0) it--;
				return it;
			}
			T const &operator * () const
			{
				return node->val;
			}
			T const *operator -> () const
			{
				return &node->val;
			}
		};
		iterator begin()
		{
			return iterator(first);
		}
		const_iterator begin() const
		{
			return const_iterator(first);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(last);
		}
		iterator end()
		{
			return iterator(0);
		}
		const_iterator end() const
		{
			return const_iterator(0);
		}
		reverse_iterator rend()
		{
			return reverse_iterator(0);
		}
		void erase(iterator it)
		{
			if (first) {
				if (it.node == first) {
					first = it.node->next;
					if (first && first->next) first->next->prev = 0;
				} else if (it.node == last) {
					last = it.node->prev;
					if (last && last->prev) last->prev->next = 0;
				} else {
					if (it.node->prev) it.node->prev->next =it.node->next;
					if (it.node->next) it.node->next->prev =it.node->prev;
				}
				if (!first || !last) {
					first = last = 0;
				}
				delete it.node;
			}
		}
		iterator insert(iterator it, T const &v)
		{
			if (first) {
				node_t *node = new node_t(v);
				if (it.node) {
					if (it.node == first) {
						node->next = first;
						if (first) first->prev = node;
						first = node;
					} else if (it.node == last) {
						node->prev = last;
						if (last) last->next = node;
						last = node;
					} else {
						node->next = it.node;
						node->prev = it.node->prev;
						if (node->prev) node->prev->next = node;
						if (node->next) node->next->prev = node;
					}
				} else {
					node_t *prev = last;
					if (prev) prev->next = node;
					node->prev = prev;
					last = node;
				}
				return iterator(node);
			} else {
				first = last = new node_t(v);
				return iterator(first);
			}
		}
		void push_back(T const &v)
		{
			insert(end(), v);
		}
	};

	template <typename T> T const *zerostring();
	template <> inline char const *zerostring<char>() { return ""; }

	template <typename T> size_t strlength(T const *p);
	template <> size_t strlength(char const *p) { return strlen(p); }

	template <typename T> class t_stringbuffer {
	private:
		struct fragment_t {
			fragment_t *next;
			size_t size;
			size_t used;
			T data[1];
		};
		struct core_t {
			unsigned int ref;
			mutable fragment_t *fragment;
			core_t()
				: ref(0)
				, fragment(0)
			{
			}
		};
		struct data_ {
			core_t *core;
			data_()
				: core(0)
			{
			}
		} data;
		void assign(core_t *p)
		{
			if (p) {
				p->ref++;
			}
			if (data.core) {
				if (data.core->ref > 1) {
					data.core->ref--;
				} else {
					internal_clear();
					delete data.core;
				}
			}
			data.core = p;
		}
		static void store(T const *ptr, T const *end, T *dst)
		{
			while (ptr < end) {
				new (dst) T(*ptr);
				ptr++;
				dst++;
			}
		}
		void internal_clear() const
		{
			while (data.core->fragment) {
				fragment_t *next = data.core->fragment->next;
				T *ptr = data.core->fragment->data;
				T *end = data.core->fragment->data + data.core->fragment->used;
				while (ptr < end) {
					ptr->~T();
					ptr++;
				}
				delete[] (char *)data.core->fragment;
				data.core->fragment = next;
			}
		}
		T *internal_get() const
		{
			if (!data.core->fragment) {
				return 0;
			}
			if (data.core->fragment->next) {
				size_t len = size();
				fragment_t *newptr = (fragment_t *)new char [sizeof(fragment_t) + sizeof(T) * len];
				newptr->next = 0;
				newptr->size = len;
				newptr->used = len;
				memset(&newptr->data[len], 0, sizeof(T));
				fragment_t *f = data.core->fragment;
				while (f && len > 0) {
					len -= f->used;
					store(f->data, f->data + f->used, newptr->data + len);
					f = f->next;
				}
				internal_clear();
				data.core->fragment = newptr;
			}
			return data.core->fragment->data;
		}
		void modify()
		{
			if (data.core->ref == 1) {
				return;
			}
			t_stringbuffer str(c_str(), size());
			assign(str.data.core);
		}
	public:
		t_stringbuffer()
		{
			assign(new core_t());
		}
		t_stringbuffer(T const *ptr)
		{
			assign(new core_t());
			print(ptr);
		}
		t_stringbuffer(T const *ptr, size_t len)
		{
			assign(new core_t());
			print(ptr, len);
		}
		t_stringbuffer(T const *begin, T const *end)
		{
			assign(new core_t());
			print(begin, end);
		}
		t_stringbuffer(t_stringbuffer const &r)
		{
			assign(r.data.core);
		}
		t_stringbuffer(vector<T> const &vec)
		{
			assign(new core_t());
			if (!vec.empty()) {
				print(&vec[0], vec.size());
			}
		}
		~t_stringbuffer()
		{
			assign(0);
		}
		void operator = (t_stringbuffer const &r)
		{
			assign(r.data.core);
		}
		void clear()
		{
			modify();
			internal_clear();
		}
		void print(T const *ptr, size_t len)
		{
			modify();
			if (ptr) {
				if (len > 0) {
					if (data.core->fragment && data.core->fragment->size > data.core->fragment->used) {
						size_t n = data.core->fragment->size - data.core->fragment->used;
						if (n > len) {
							n = len;
						}
						store(ptr, ptr + n, data.core->fragment->data + data.core->fragment->used);
						data.core->fragment->used += n;
						data.core->fragment->data[data.core->fragment->used] = 0;
						ptr += n;
						len -= n;
					}
					if (len > 0) {
						size_t n = 4096;
						if (n < len) {
							n = len;
						}
						fragment_t *newptr = (fragment_t *)new char [sizeof(fragment_t) + sizeof(T) * n];
						newptr->next = data.core->fragment;
						newptr->size = n;
						newptr->used = len;
						store(ptr, ptr + len, newptr->data);
						newptr->data[newptr->used] = 0;
						data.core->fragment = newptr;
					}
				}
			}
		}
		void print(T const *begin, T const *end)
		{
			print(begin, end - begin);
		}
		void print(T const *ptr)
		{
			print(ptr, strlength(ptr));
		}
		void print(T const &t)
		{
			print(&t, 1);
		}
		void print(t_stringbuffer const &r)
		{
			print(r.c_str(), r.size());
		}
		size_t size() const
		{
			size_t len = 0;
			fragment_t *f = data.core->fragment;
			while (f) {
				len += f->used;
				f = f->next;
			}
			return len;
		}
		bool empty() const
		{
			return size() == 0;
		}
		T const *c_str() const
		{
			T *p = internal_get();
			return p ? p : zerostring<T>();
		}
		int compare(t_stringbuffer const &r) const
		{
			if (data.core == r.data.core) return true;
			if (empty() && r.empty()) return true;
			return t_strcmp(c_str(), r.c_str());
		}
		T operator [] (size_t i) const
		{
			return c_str()[i];
		}
		bool operator == (t_stringbuffer const &r) const
		{
			return compare(r) == 0;
		}
		bool operator != (t_stringbuffer const &r) const
		{
			return compare(r) != 0;
		}
		bool operator < (t_stringbuffer const &r) const
		{
			return compare(r) < 0;
		}
		bool operator > (t_stringbuffer const &r) const
		{
			return compare(r) > 0;
		}
		bool operator <= (t_stringbuffer const &r) const
		{
			return compare(r) <= 0;
		}
		bool operator >= (t_stringbuffer const &r) const
		{
			return compare(r) >= 0;
		}

		t_stringbuffer operator += (t_stringbuffer const &s)
		{
			print(s);
			return *this;
		}
		t_stringbuffer operator += (T const *s)
		{
			print(s);
			return *this;
		}
		t_stringbuffer operator += (T s)
		{
			print(s);
			return *this;
		}
	};

	// operator +

	template <typename T> inline t_stringbuffer<T> operator + (t_stringbuffer<T> const &left, t_stringbuffer<T> const &right)
	{
		t_stringbuffer<T> t = left;
		t.print(right);
		return t;
	}

	template <typename T> inline t_stringbuffer<T> operator + (t_stringbuffer<T> const &left, char const *right)
	{
		return left + t_stringbuffer<T>(right);
	}

	template <typename T> inline t_stringbuffer<T> operator + (char const *left, t_stringbuffer<T> const &right)
	{
		return t_stringbuffer<T>(left) + right;
	}

	template <typename T> inline t_stringbuffer<T> operator + (t_stringbuffer<T> const &left, char right)
	{
		return left + t_stringbuffer<T>(right);
	}

	template <typename T> inline t_stringbuffer<T> operator + (char left, t_stringbuffer<T> const &right)
	{
		return t_stringbuffer<T>(left) + right;
	}

	typedef t_stringbuffer<char> string;

} // namespace tiny

#endif
