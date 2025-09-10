#include "compare.h"

CompareFiles::CompareFiles(const std::string &str1, const std::string &str2){
	p1 = str1;
	p2 = str2;
	common = longestCommonSubsequence(readFile(p1), readFile(p2));

}

CompareFiles::CompareFiles(const fs::path &path1, const fs::path &path2){
	p1 = path1;
	p2 = path2;
	common = longestCommonSubsequence(readFile(p1.string()), readFile(p2.string()));
}

std::string readFile(const std::string &fileName){
	std::ifstream file(fileName);
	if(!file.is_open()){
		throw std::runtime_error("Could not open file:" + fileName);
	}
	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return content;
}

void CompareFiles::show_stats() const {
	std::cout << "Pair: " <<p1 << ", "<<p2<<"\nCommon subsequence length: "<< common.length()<<"\nOverlap: " << common << std::endl;
}

std::string CompareFiles::longestCommonSubsequence(std::string X, std::string Y){
	int m = X.size();
	int n = Y.size();

	std::string lcs;
	std::vector<std::vector<int> > dp(m+1, std::vector<int>(n+1));

	for (int i = 1; i <= m; i++){
		for (int j = 1; j <= n; j++){
			if (X[i-1] ==Y[j-1]){
				dp[i][j] = dp[i-1][j-1] +1;}
			else {
				dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);}
		}
	}
	
	int i = m;
	int j = n;
	while (i>0 && j>0){
		if (X[i-1] == Y[j-1]){
			lcs.push_back(X[i-1]);
			i -= 1;
			j -= 1; }
		else if (dp[i-1][j]>dp[i][j-1]){
			i -=1; }
		else{
			j -=1; }
	}
//	int len = lcs.length();
//	std::string rev;
       
//    	for (int i = len - 1; i >= 0; i--){	
//		rev.push_back(lcs[i]);}
//	return rev;
	std::reverse(lcs.begin(), lcs.end());
	return lcs;
}
