#include <vector>
#include <memory>

template <typename KeyType, typename ValueType, typename Hash = std::hash<KeyType>>
class HashTable
{
public:
	class iterator;
	using pair_KV = std::pair<KeyType, ValueType>;
	using pair_ptr = std::unique_ptr<pair_KV>;

	HashTable() { map = move(std::vector<std::vector<pair_ptr>>(5)); }
	HashTable(const Hash& h) : hash(h) { map = move(std::vector<std::vector<pair_ptr>>(5)); }

	ValueType& operator [] (const KeyType& key)
	{
		int index = hash(key) % map.size();
		for (const auto& item: map[index])
			if (item->first == key)
				return item->second;

		insert(key, ValueType(), map);
		if (map[index].size() >= max_cell)
		{
			rebuild();
			index = hash(key) % map.size();
		}

		++size;
		return map[index].back()->second;
	}

	void erase(const KeyType& key)
	{
		int index = hash(key);
		for (size_t i = 0; i < map[index].size(); ++i)
			if (map[index][i]->first == key)
			{
				--size;
				map[index].erase(map[index].begin() + i);
				if (size < map.size()) rebuild();
				return;
			}
	}

	iterator begin() { return iterator(*this, 0); }
	iterator end() { return iterator(*this, map.size()); }

	class iterator
	{
	public:
		iterator () {}
		iterator(const HashTable& _table, size_t _cell) : table(_table), cell(_cell) { update(); }
		iterator& operator ++ ()
		{
			++position;
			update();
			return *this;
		}

		std::pair<KeyType, ValueType>& operator*() const
		{
			return *(table.map[cell][position]);
		}

		std::pair<KeyType, ValueType>* operator->() const
		{
			return &*(table.map[cell][position]);
		}

		bool operator == (const iterator& other)
		{
			return cell == other.cell && position == other.position;
		}

		bool operator != (const iterator& other)
		{
			return cell != other.cell || position != other.position;
		}

	private:
		const HashTable& table = nullptr;
		size_t cell;
		size_t position = 0;

		void update()
		{
			while (cell < table.map.size() && position == table.map[cell].size())
			{
				++cell;
				position = 0;
			}
		}
	};

private:
	const Hash& hash = Hash();
	size_t size = 0;
	size_t max_cell = 10;
	std::vector<std::vector<pair_ptr>> map;

	void rebuild()
	{
		std::vector<std::vector<pair_ptr>> temp(map.size() * 2);
		for (size_t i = 0; i < map.size(); ++i)
			for (auto& item: map[i])
				insert(item->first, item->second, temp);

		swap(map, temp);
	}

	void insert(KeyType key, ValueType value, std::vector<std::vector<pair_ptr>>& _map)
	{
		int index = hash(key) % _map.size();
		pair_ptr ptr = std::make_unique<pair_KV>(std::make_pair(key, value));
		_map[index].push_back(move(ptr));
	}
};
