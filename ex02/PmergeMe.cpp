#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
    oddVector = -1;
    oddDeque = -1;
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void) other;
    return *this;
}

PmergeMe::~PmergeMe()
{

}

void	PmergeMe::sort(int argc, char **argv )
{
	if (!PmergeMe::validateUserInput(argc, argv))
        return ;
	PmergeMe::printBeforeSorting();
	PmergeMe::sortVector();
	PmergeMe::sortDeque();
}

void    PmergeMe::printBeforeSorting(void)
{
    std::cout << "Before: ";
    for (size_t i = 0; i < inputVector.size(); i++)
    {
        std::cout << inputVector[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

template<typename T>
void    PmergeMe::printAfterSorting(clock_t start, const T& seq, std::string type)
{
    clock_t end = clock();
    double timePassedMs = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;
    std::cout << "After : ";
    for (size_t i = 0; i < seq.size(); i ++)
    {
        std::cout << seq[i] << " ";
    }
    std::cout << "\nTime to process a range of " << seq.size()  << " elements with " << type << " : " << timePassedMs << "ms" << std::endl;
}

bool    PmergeMe::validateUserInput(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        int length = std::strlen(argv[i]);
        for (int j = 0; j < length; j++)
        {
            if (!std::isdigit(argv[i][j]))
            {
                std::cout << "[ERROR] invalid argument" << std::endl;
                return false;
            }
        }
        if (std::strlen(argv[i]) > 10 || std::atoll(argv[i]) > 2147483647)
        {
            std::cout << "[ERROR] overflow" << std::endl;
            return false;
        }
        int num = atoi(argv[i]);
        if (num < 0)
        {
            std::cout << "[ERROR] cannot process negative number" << std::endl;
            return false;
        }
        std::vector<int>::iterator it;
        it = std::find(inputVector.begin(), inputVector.end(), num);
        if (it != inputVector.end())
        {
            std::cout << "[ERROR] cannot insert duplicate number" << std::endl;
            return false;
        }
        inputVector.push_back(num);
        inputDeque.push_back(num);
    }
        return true;
    }
    

template<typename T>
int PmergeMe::binarySearch(T& container, int target, int begin, int end)
{
	int mid;

	while (begin <= end)
	{
		mid = begin + (end - begin) / 2;
		if (target == container.at(mid))
			return (mid);

		if (target > container.at(mid))
			begin = mid + 1;
		else
			end = mid - 1;
	}
	if (target > container.at(mid))
		return (mid + 1);
	else
		return (mid);
}

int PmergeMe::getJacobsthal(int n)
{
    if (n== 0)
		return (0);
    if (n == 1)
		return (1);

    int prev1 = 0;
    int prev2 = 1;
    int current = 0;

    for (int i = 2; i <= n; ++i)
	{
        current = prev1 + 2 * prev2;
        prev1 = prev2;
        prev2 = current;
    }
    return current;
}

void	PmergeMe::sortVector( void )
{
	clock_t start = clock();
	size_t	size = inputVector.size();
	if (size == 1)  // 입력값이 하나일 때 특별한 처리
    {
        mainVector.push_back(inputVector[0]);
        PmergeMe::printAfterSorting(start, mainVector, "vector");
        return;
    }
	if (size % 2 == 1) //홀수면 마지막 언페얼드를 오드벡터에
	{
		oddVector = inputVector.back();
		inputVector.pop_back();
        size--;
	}

	for (size_t i = 0; i < size - 1; i += 2) {
		// 페어를 생성하면서 동시에 값들을 비교
		if (inputVector[i] < inputVector[i + 1]) {
			// 큰 값은 _mainVector에, 작은 값은 _pendVector에 넣음
			mainVector.push_back(inputVector[i + 1]);
			subVector.push_back(inputVector[i]);
		} else {
			// 큰 값은 _mainVector에, 작은 값은 _pendVector에 넣음
			mainVector.push_back(inputVector[i]);
			subVector.push_back(inputVector[i + 1]);
		}
	}
	PmergeMe::mergeSort(mainVector, 0, mainVector.size() - 1);
    PmergeMe::mergeSort(subVector, 0, subVector.size() - 1);;
	mainVector.insert(mainVector.begin(), subVector[0]);
	PmergeMe::insertNumbersVector();
	PmergeMe::printAfterSorting(start, mainVector, "vector");
}

void	PmergeMe::sortDeque( void )
{
	clock_t start = clock();
	size_t	size = inputDeque.size();
	
    if (size == 1)  // 입력값이 하나일 때 특별한 처리
    {
        mainDeque.push_back(inputDeque[0]);
        PmergeMe::printAfterSorting(start, mainDeque, "deque");
        return;
    }
	if (size % 2 == 1)
	{
		oddDeque = inputDeque.back();
		inputDeque.pop_back();
        //size--;
	}
	for (size_t i = 0; i < size - 1; i += 2) {
		// 페어를 생성하면서 동시에 값들을 비교
		if (inputDeque[i] < inputDeque[i + 1]) {
			// 큰 값은 _mainVector에, 작은 값은 _pendVector에 넣음
			mainDeque.push_back(inputDeque[i + 1]);
			subDeque.push_back(inputDeque[i]);
		} else {
			// 큰 값은 _mainVector에, 작은 값은 _pendVector에 넣음
			mainDeque.push_back(inputDeque[i]);
			subDeque.push_back(inputDeque[i + 1]);
		}
	}
	
	mergeSort(mainDeque, 0, mainDeque.size() - 1);
    mergeSort(subDeque, 0, subDeque.size() - 1);
	mainDeque.push_front(subDeque[0]);
	insertNumbersDeque();
	printAfterSorting(start, mainDeque, "deque");
}

template <typename T>
void PmergeMe::mergeSort( T& vector, int start, int end )
{
    if (start >= end)
        return;

    int mid = (start + end) / 2;

    PmergeMe::mergeSort(vector, start, mid);
    PmergeMe::mergeSort(vector, mid + 1, end);

    std::vector<int> sorted;

    int left = start;
    int right = mid + 1;

    while (left <= mid && right <= end)
	{
        if (vector[left] <= vector[right]) {
            sorted.push_back(vector[left]);
            left++;
        } else {
            sorted.push_back(vector[right]);
            right++;
        }
    }
    while (left <= mid)
	{
        sorted.push_back(vector[left]);
        left++;
    }
    while (right <= end)
	{
        sorted.push_back(vector[right]);
        right++;
    }
    for (int i = start; i <= end; i++)
        vector[i] = sorted[i - start];
}

template<typename T>
void PmergeMe::jacobsthalInsertSequence(size_t maxSize, T& jacobsthalSequence)
{
	size_t	jacobIndex;
	int		index;

	index = 3;
	while ((jacobIndex = PmergeMe::getJacobsthal(index)) < maxSize) //maxSize == 정렬할 배열 크기, 거기까지 야콥스타일 수 배열 가져옴
	{
		jacobsthalSequence.push_back(jacobIndex); //sequence에 저장... 야콥스타일 수가 맥스 사이즈 넘지 않을때 까지만 하면 됨
		index++;
	}
}

void PmergeMe::getSubvectorInsertionPosition( void )
{
    if (this->subVector.empty())
        return;
    PmergeMe::jacobsthalInsertSequence(subVector.size(), this -> jacobsthalVectorSequence); 
    size_t lastPos = 1;
    size_t val = 1;
    for (size_t i = 0; i < this -> jacobsthalVectorSequence.size(); i++) //야콥스탈 넘버 11이면 11까지 회전
    {
        val = jacobsthalVectorSequence.at(i); //1 3 5 11 이런식으로 있으니까11 넣고
        subVectorInsertionPosition.push_back(val);

        size_t pos = val - 1; //역순으로 10 9 8 7 6 으로 넣어야되니까 그거 함
        while (pos > lastPos)
        {
            subVectorInsertionPosition.push_back(pos);
            pos--;
        }
        lastPos = val;
    }

    while (val++ < subVector.size()) 
        subVectorInsertionPosition.push_back(val);
}

void PmergeMe::insertNumbersVector( void )
{
	std::vector<int>::iterator	it;
    size_t	addCount = 0;

    PmergeMe::getSubvectorInsertionPosition();
	for (it = subVectorInsertionPosition.begin(); it < subVectorInsertionPosition.end(); it++)
    {
        int nbr = subVector.at(*it - 1); //먼저 빼야될 원소의 인덱스를 저장해둔 벡터를 순환하면서 해당 위치에 있는 서브체인 원소 빼기
        size_t endPos = *it + addCount; //addCount는 이미 삽입된 원소의 갯수를 고려하기 우히ㅏㅁ
        size_t pos = PmergeMe::binarySearch(mainVector, nbr, 0, endPos); //메인체인에서 넣을 위치 찾기
        mainVector.insert(mainVector.begin() + pos, nbr); //넣기
		addCount++;
    }
    if (oddVector != -1)
    {
        size_t nbr = oddVector;
        size_t pos = PmergeMe::binarySearch(mainVector, nbr, 0, mainVector.size() - 1);
        mainVector.insert(mainVector.begin() + pos, nbr);
    }
}

void PmergeMe::getSubDequeInsertionPosition( void )
{
	if (subDeque.empty())
		return;

	PmergeMe::jacobsthalInsertSequence(subDeque.size(), this -> jacobsthalDequeSequence);
	size_t lastPos = 1;
	size_t val = 1;

	while (!jacobsthalDequeSequence.empty())
	{
		val = jacobsthalDequeSequence.front();

		jacobsthalDequeSequence.pop_front();
		subDequeInsertionPosition.push_back(val);

		size_t pos = val - 1;
		while (pos > lastPos)
		{
			subDequeInsertionPosition.push_back(pos);
			pos--;
		}
		lastPos = val;
	}
	while (val++ < subDeque.size())
	    subDequeInsertionPosition.push_back(val);
}

void PmergeMe::insertNumbersDeque( void )
{
	std::deque<int>::iterator it;
	size_t addCount = 0;

	PmergeMe::getSubDequeInsertionPosition();
    std::cout << std::endl;
	for (it = subDequeInsertionPosition.begin(); it < subDequeInsertionPosition.end(); it++)
	{
		int n = subDeque.at(*it - 1);
		size_t endPos = *it + addCount;
		size_t pos = PmergeMe::binarySearch(mainDeque, n, 0, endPos);
		mainDeque.insert(mainDeque.begin() + pos, n);
		addCount++;
	}
	if (oddDeque != -1)
	{
		size_t nbr = oddDeque;
		size_t pos = PmergeMe::binarySearch(mainDeque, nbr, 0, mainDeque.size() - 1);
		mainDeque.insert(mainDeque.begin() + pos, nbr);
	}
}