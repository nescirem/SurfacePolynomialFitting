#include <iostream>

#include "rapidcsv.h"
#include "Eigen/Dense"
#include "PROJECT_DIR.h"


struct Data
{
	struct Point
	{
		double x, y, z;
	};

	Data(int row, int col)
	{
		n_row = row;
		n_col = col;
		points.resize(n_row * n_col);
	}

	std::vector<Point> points;
	int n_row = 0;
	int n_col = 0;
};

std::vector<double> convertVStr2VDou(const std::vector<std::string>& vstr)
{
    std::vector<double> vdou;
    for (const std::string& str : vstr)
    {
        try {
            double value = std::stod(str);
            vdou.push_back(value);
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range: " << e.what() << std::endl;
        }
    }
    return vdou;
}

Data loadDataMatrix()
{
    std::string path = PROJECT_PATH;
    path += "/data.csv";
    rapidcsv::Document doc(path, rapidcsv::LabelParams(0, 0), rapidcsv::SeparatorParams(), rapidcsv::ConverterParams(true), rapidcsv::LineReaderParams(true, '#', true));
    size_t n_row = doc.GetRowCount();
    size_t n_col = doc.GetColumnCount();

    Data data(n_row, n_col);
    std::vector<double> row_titles = convertVStr2VDou(doc.GetRowNames());
    std::vector<double> col_titles = convertVStr2VDou(doc.GetColumnNames());

    int id = 0;
    for (size_t i = 0; i < n_col; ++i)
    {
        std::vector<double> zs = doc.GetColumn<double>(i);
        for (size_t j = 0; j < zs.size(); ++j)
        {
            if (!std::isfinite(zs[j])) continue;
            data.points[id].x = col_titles[i];
            data.points[id].y = row_titles[j];
            data.points[id].z = zs[j];
            ++id;
        }
    }
    return data;
}

double calculateR2(const Eigen::VectorXd& observed, const Eigen::VectorXd& predicted) {
    double meanObserved = observed.mean();
    double totalSumOfSquares = (observed.array() - meanObserved).square().sum();
    double residualSumOfSquares = (observed - predicted).array().square().sum();

    double rSquared = 1.0 - (residualSumOfSquares / totalSumOfSquares);
    return rSquared;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    int N = 2;
    try
    {
        N = std::atoi(args[1].c_str());
    }
    catch (const std::exception&)
    {
        std::cerr << "Bad order settings!" << std::endl;
    }

    Data data = loadDataMatrix();
    int m = data.n_col * data.n_row;
    if (m < 3)
    {
        std::cerr << "Bad data input!" << std::endl;
    }

    std::cout << N << "-Order fitting " << data.n_row << "*" << data.n_col << " data..." << std::endl;
    
    Eigen::MatrixXd X(m, (N + 1) * (N + 2) / 2);
    Eigen::VectorXd Z(m);

    for (int k = 0; k < m; ++k) {
        double x = data.points[k].x;
        double y = data.points[k].y;
        double z = data.points[k].z;

        int index = 0;
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N - i; ++j) {
                X(k, index++) = std::pow(x, i) * std::pow(y, j); // C_{00},C{01},...
                //X(k, index++) = std::pow(x, j) * std::pow(y, i); // C_{00},C_{10},...
            }
        }
        Z(k) = z;
    }

    Eigen::MatrixXd C = (X.transpose() * X).ldlt().solve(X.transpose() * Z);
    std::cout << "Parameters C:\n" << C << std::endl;

    Eigen::VectorXd predicted = X * C;
    double rSquared = calculateR2(Z, predicted);
    std::cout << "-----------------------" << std::endl;
    std::cout << "R-squared: " << rSquared << std::endl;

    return 0;
}
