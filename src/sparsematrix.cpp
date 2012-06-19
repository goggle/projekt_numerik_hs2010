#include "sparsematrix.h"

SparseMatrix::SparseMatrix(): size(0) {
	#ifndef NDEBUG
	cout << "Empty Sparse Matrix created." << endl;
	#endif
	//rows = new list<MatrixEntry*>[0];
	//cols = new list<MatrixEntry*>[0];
}


SparseMatrix::SparseMatrix(int s): size(s)
{
	rows = new list<MatrixEntry*>[s];
	cols = new list<MatrixEntry*>[s];
	#ifndef NDEBUG
	cout << "Sparse Matrix with " << s << " entries created." << endl;
	#endif
}

// TODO: Bugfixing:
SparseMatrix::SparseMatrix(const SparseMatrix &M): size(M.getSize())
{
	rows = new list<MatrixEntry*>[size];
	cols = new list<MatrixEntry*>[size];
	for (int k = 0; k < size; k++) {
		rows[k] = M.getRowList(k);
		cols[k] = M.getColList(k);
	}
	#ifndef NDEBUG
	cout << "WARNING: Sparse Matrix copied. This Constructor doesn't work correctly..." << endl;
	#endif
}


SparseMatrix::~SparseMatrix()
{
	if (size != 0) {
		list<MatrixEntry*> *rowlist;
		list<MatrixEntry*>::iterator iter;
		for (int i = 0; i < size; i++) {
			rowlist = &rows[i];
			for (iter = rowlist->begin(); iter != rowlist->end(); iter++) {
				delete *iter;
			}
		}
		delete[] rows;
		delete[] cols;
		#ifndef NDEBUG
		cout << "Sparse Matrix with " << size << " entries deleted." << endl;
		#endif
	}
	else {
	#ifndef NDEBUG
	cout << "Empty Sparse Matrix deleted." << endl;
	#endif
	}
}


SparseMatrix& SparseMatrix::operator= (const SparseMatrix &mat)
{
	#ifndef NDEBUG
	cout << "Sparse Matrix Assignment Operator." << endl;
	#endif
	if (this == &mat)
		return *this;
	

	if (size != 0) {
		list<MatrixEntry*> *rowlist;
		list<MatrixEntry*>::iterator iter;
		for (int i = 0; i < size; i++) {
			rowlist = &rows[i];
			for (iter = rowlist->begin(); iter != rowlist->end(); iter++) {
				delete *iter;
			}
		}
		delete[] rows;
		delete[] cols;
	}
	
	size = mat.size;
	rows = new list<MatrixEntry*>[size];
	cols = new list<MatrixEntry*>[size];
//	for (int k = 0; k < size; k++) {
//		rows[k].resize(mat.rows[k].size());
//		cols[k].resize(mat.cols[k].size());
//		copy(mat.rows[k].begin(), mat.rows[k].end(), rows[k].begin());
//		copy(mat.cols[k].begin(), mat.cols[k].end(), cols[k].begin());
//	}
	int i, j;
	double val;
	list<MatrixEntry*>::iterator iter;

	for (int k = 0; k < size; k++) {
		iter = mat.rows[k].begin();
		while (iter != mat.rows[k].end()) {
			i = (*iter)->getRow();
			j = (*iter)->getCol();
			val = (*iter)->getValue();
			setEntry(i, j, val);
			++iter;
		}
	}
	
	//size = mat.size;
	//rows = new list<MatrixEntry*>[size];
	//cols = new list<MatrixEntry*>[size];
	//for (int i = 0; i < size; i++) {
	//	rows[i] = mat.rows[i];
	//	cols[i] = mat.cols[i];
	//}

	return *this;
}


SparseMatrix& SparseMatrix::operator*= (const double a)
{
	double val;
	list<MatrixEntry*> *rowlist;
	list<MatrixEntry*>::iterator iter;
	for (int k = 0; k < size; k++) {
		rowlist = &rows[k];
		iter = rowlist->begin();
		while (iter != rowlist->end()) {
			val = (*iter)->getValue();
			val *= a;
			(*iter)->setValue(val);
			++iter;
		}
	}
	return *this;
}

void SparseMatrix::setEntry(int i, int j, double val)
{
	#ifndef NDEBUG
	if (i < 0 || i >= size || j < 0 || j >= size) {
		cerr << "SparseMatrix: Out of range!" << endl;
		return;
	}
	#endif

	if (abs(val) < ZERO_EPS)
		return;

	list<MatrixEntry*> *rowList = &rows[i];
	list<MatrixEntry*> *colList = &cols[j];

	MatrixEntry *entry = new MatrixEntry(i, j, val);
	
	list<MatrixEntry*>::iterator iter = rowList->begin();
	// Insert the pointer in the row list:
	if (rowList->empty()) {
		rowList->push_back(entry);
	}
	else if (j == (*iter)->getCol()) {
		(*iter)->setValue(val);
		delete entry;
		return;
	}
	else {
		list<MatrixEntry*>::iterator iterNext = rowList->begin();
		iterNext++;
		if (j < (*iter)->getCol())
			rowList->insert(iter, entry);
		else {
			while (iterNext != rowList->end()) {
				if ((*iterNext)->getCol() < j) {
					iter++;
					iterNext++;
				}
				else if ((*iterNext)->getCol() == j) {
					(*iterNext)->setValue(val);
					delete entry;
					return;
				}
				else {
					rowList->insert(iterNext, entry);
					break;
				}
			}
			if (iterNext == rowList->end())
				rowList->push_back(entry);
		}
	}

	// Insert the pointer in the column list:
	iter = colList->begin();
	if (colList->empty()) {
		colList->push_back(entry);
	}
	else if (i == (*iter)->getRow()) {
		cerr << "Shit happens." << endl;
		return;
	}
	else {
		list<MatrixEntry*>::iterator iterNext = colList->begin();
		iterNext++;
		if (i < (*iter)->getRow())
			colList->insert(iter, entry);
		else {
			while (iterNext != colList->end()) {
				if ((*iterNext)->getRow() < i) {
					iter++;
					iterNext++;
				}
				else if ((*iterNext)->getRow() == i) {
					//(*iterNext)->setValue(val); // should not be necessary
					cerr << "Shit happens" << endl;
					break;
				}
				else {
					colList->insert(iterNext, entry);
					break;
				}
			}
			if (iterNext == colList->end())
				colList->push_back(entry);
		}
	}
}


void SparseMatrix::addEntry(int i, int j, double val)
{
	#ifndef NDEBUG
	if (i < 0 || i >= size || j < 0 || j >= size) {
		cerr << "SparseMatrix: Out of range!" << endl;
		return;
	}
	#endif
	
	if (abs(val) < ZERO_EPS)
		return;

	list<MatrixEntry*> *rowList = &rows[i];
	list<MatrixEntry*> *colList = &cols[j];

	MatrixEntry *entry = new MatrixEntry(i, j, val);
	
	// Insert the pointer in the row list:
	list<MatrixEntry*>::iterator iter = rowList->begin();
	if (rowList->empty()) {
		rowList->push_back(entry);
	}
	else if (j == (*iter)->getCol()) {
		(*iter)->addValue(val);
		//if (abs((*iter)->getValue()) < ZERO_EPS) {
		//	iter = rowList->erase(iter);
		//}
		delete entry;
		return;
	}
	else {
		list<MatrixEntry*>::iterator iterNext = rowList->begin();
		iterNext++;
		if (j < (*iter)->getCol())
			rowList->insert(iter, entry);
		else {
			while (iterNext != rowList->end()) {
				if ((*iterNext)->getCol() < j) {
					iter++;
					iterNext++;
				}
				else if ((*iterNext)->getCol() == j) {
					(*iterNext)->addValue(val);
					//if (abs((*iterNext)->getValue()) < ZERO_EPS) {
					//	iterNext = colList->erase(iterNext);
					//}
					delete entry;
					return;
				}
				else {
					rowList->insert(iterNext, entry);
					break;
				}
			}
			if (iterNext == rowList->end())
				rowList->push_back(entry);
		}
	}

	// Insert the pointer in the column list:
	iter = colList->begin();
	if (colList->empty()) {
		colList->push_back(entry);
	}
	else if (i == (*iter)->getRow()) {
		cerr << "Shit happens." << endl;
		return;
	}
	else {
		list<MatrixEntry*>::iterator iterNext = colList->begin();
		iterNext++;
		if (i < (*iter)->getRow())
			colList->insert(iter, entry);
		else {
			while (iterNext != colList->end()) {
				if ((*iterNext)->getRow() < i) {
					iter++;
					iterNext++;
				}
				else if ((*iterNext)->getRow() == i) {
					cerr << "Shit happens." << endl;
					return;
				}
				else {
					colList->insert(iterNext, entry);
					break;
				}
			}
			if (iterNext == colList->end())
				colList->push_back(entry);
		}
	}

}

double SparseMatrix::getValue(const int i, const int j) const
{
	list<MatrixEntry*> *rowlist = &rows[i];
	list<MatrixEntry*>::iterator iter = rowlist->begin();
	if (rowlist->empty())
		return 0.0;
	else {
		while (iter != rowlist->end()) {
			if ((*iter)->getCol() == j)
				return (*iter)->getValue();
			else if ((*iter)->getCol() > j)
				return 0.0;
			iter++;
		}
	}
	return 0.0;
}


void SparseMatrix::printViaRows()
{
	list<MatrixEntry*> *rowlist;
	list<MatrixEntry*>::iterator iter;
	for (int i = 0; i < size; i++) {
		rowlist = &rows[i];
		for (iter = rowlist->begin(); iter != rowlist->end(); iter++) {
			cout << **iter << endl;
		}
	}
}

void SparseMatrix::printViaColumns()
{
	list<MatrixEntry*> *collist;
	list<MatrixEntry*>::iterator iter;
	for (int i = 0; i < size; i++) {
		collist = &cols[i];
		for (iter = collist->begin(); iter != collist->end(); iter++) {
			cout << **iter << endl;
		}
	}
}


Vector SparseMatrix::operator* (const Vector &x) 
{
	Vector result = Vector(size);

	list<MatrixEntry*> *rowlist;
	list<MatrixEntry*>::iterator iter;
	double res = 0.0;
	int ind;
	double a;

	for (int k = 0; k < size; k++) {
		rowlist = &rows[k];
		for (iter = rowlist->begin(); iter != rowlist->end(); iter++) {
			a = (*iter)->getValue();
			ind = (*iter)->getCol();
			res += a * x[ind];
		}
		result.setEntry(k, res);
		res = 0.0;
	}
	return result;
}

// NOTE: This is very bad style:... sorry...
Vector& SparseMatrix::multiplyVector(const Vector &x, Vector &res)
{
	list<MatrixEntry*> *rowlist;
	list<MatrixEntry*>::iterator iter;
	int ind;
	double r = 0.0;
	double a;
	
	for (int k = 0; k < size; k++) {
		rowlist = &rows[k];
		for (iter = rowlist->begin(); iter != rowlist->end(); iter++) {
			a = (*iter)->getValue();
			ind = (*iter)->getCol();
			r += a * x[ind];
		}
		res.setEntry(k, r);
		r = 0.0;
	}
	return res;
}


SparseMatrix SparseMatrix::operator+ (const SparseMatrix &M)
{
	#ifndef NDEBUG
	if (getSize() != M.getSize())
		cerr << "Error in Addation of Sparse Matrices: Dimension mismatch!" << endl;
	#endif
	
	SparseMatrix A(getSize());

	list<MatrixEntry*> *rowlist;
	list<MatrixEntry*> *rowlistM;
	list<MatrixEntry*> *rowlistA;

	
	list<MatrixEntry*>::iterator iter;
	list<MatrixEntry*>::const_iterator iterM;
	double val, valM;

	int i, j;
	double d;

	for (int k = 0; k < size; k++) {
		rowlist = &rows[k];
		rowlistM = &(M.rows[k]);
		rowlistA = &(A.rows[k]);
		iter = rowlist->begin();
		iterM = rowlistM->begin();
		while ( (iter != rowlist->end()) && (iterM != rowlistM->end()) ) {
			if ((*iter)->getCol() == (*iterM)->getCol()) {
				val = (*iter)->getValue();
				valM = (*iterM)->getValue();
				i = (*iter)->getRow();
				j = (*iter)->getCol();
				d = val + valM;
				MatrixEntry *entry = new MatrixEntry(i, j, d);
				rowlistA->push_back(entry);
				++iter;
				++iterM;
			}
			else if ((*iter)->getCol() < (*iterM)->getCol()) {
				i = (*iter)->getRow();
				j = (*iter)->getCol();
				val = (*iter)->getValue();
				MatrixEntry *entry = new MatrixEntry(i, j, val);
				rowlistA->push_back(entry);
				++iter;
			}
			else {
				i = (*iterM)->getRow();
				j = (*iterM)->getCol();
				valM = (*iterM)->getValue();
				MatrixEntry *entry = new MatrixEntry(i, j, valM);
				rowlistA->push_back(entry);
				++iterM;
			}
		}
		while (iter != rowlist->end()) {
			i = (*iter)->getRow();
			j = (*iter)->getCol();
			val = (*iter)->getValue();
			MatrixEntry *entry = new MatrixEntry(i, j, val);
			rowlistA->push_back(entry);
			++iter;
		}
		while (iterM != rowlistM->end()) {
			i = (*iterM)->getRow();
			j = (*iterM)->getCol();
			valM = (*iterM)->getValue();
			MatrixEntry *entry = new MatrixEntry(i, j, valM);
			rowlistA->push_back(entry);
			++iterM;
		}
	}
	return A;
}


Vector SparseMatrix::conjugateGradient(const Vector &b) {
	#ifndef NDEBUG
	cout << "Entering Conjugate Gradient method:" << endl;
	#endif

	const double eps = 1e-12;
	int n_iter = 1;

	//Vector x = Vector(size);
	Vector x(size);

	if (size != b.getDim()) {
		cerr << "Conjugate Gradient: Dimension mismatch!" << endl;
		return x;
	}
	
	//Vector r = b;
	//Vector p = r;
	//Vector Ap = Vector(size);
	Vector r(b);
	Vector p(r);
	Vector Ap(size);

	double rsold, rsnew;
	double alpha;
	//double beta;

	
	rsold = r*r;
	while (true) {
		//Ap = (*this) * p;
		multiplyVector(p, Ap);
		alpha = rsold/(p * Ap);
		x.addVectorMultByScalar(alpha, p);
		r.addVectorMultByScalar(-alpha, Ap);
		rsnew = r*r;
		if ( sqrt(rsnew) < eps ) {
			#ifndef NDEBUG
			cout << "Conjugate Gradient method ended after " << n_iter << " iterations." << endl;
			#endif
			return x;
		}
		//beta = rsnew/rsold;
		p.multByScalarAddVector(rsnew/rsold, r);
		rsold = rsnew;
		n_iter++;

		#ifndef NDEBUG
		if (n_iter > size) {
			cerr << "Error: Conjugate Gradient method did not converge!" << endl;
			return x;
		}
		#endif
	}
	return x;
}

Vector SparseMatrix::getJacobiPreconditioner()
{
	Vector M(size);
	double val;
	for (int k = 0; k < size; k++) {
		val = 1.0/getValue(k, k);
		M.setEntry(k, val);
	}

	return M;
}


Vector SparseMatrix::preconditionedConjugateGradient(const Vector &b)
{
	#ifndef NDEBUG
	cout << "Entering Preconditioned Conjugate Gradient method:" << endl;
	#endif

	const double eps = 1e-12;
	int n_iter = 1;

	//Vector x = Vector(size);
	Vector x(size);

	if (size != b.getDim()) {
		cerr << "Preconditioned Conjugate Gradient: Dimension mismatch!" << endl;
		return x;
	}
	
	Vector r(b);
	Vector Minv;
	Minv = getJacobiPreconditioner();
	Vector z(size);
	z.vecmul(Minv, r);
	Vector p(z);
	Vector Ap(size);

	double rsold, rsnew;
	double alpha;
	//double beta;

	
	rsold = r*z;
	rsnew = rsold;
	while (true) {
		//Ap = (*this) * p;
		multiplyVector(p, Ap);
		alpha = rsold/(p * Ap);
		x.addVectorMultByScalar(alpha, p);
		r.addVectorMultByScalar(-alpha, Ap);
		//rsnew = r*r;
		if ( r.norm() < eps ) {
			#ifndef NDEBUG
			cout << "Preconditioned Conjugate Gradient method ended after " << n_iter << " iterations." << endl;
			#endif
			return x;
		}
		//beta = rsnew/rsold;
		z.vecmul(Minv, r);
		rsnew = r * z;
		p.multByScalarAddVector(rsnew/rsold, z);
		rsold = rsnew;
		n_iter++;

		#ifndef NDEBUG
		if (n_iter > size) {
			cerr << "Error: Preconditioned Conjugate Gradient method did not converge!" << endl;
			return x;
		}
		#endif
	}
	return x;
}



Vector SparseMatrix::cgs(const Vector &b)
{
	#ifndef NDEBUG
	cout << "Entering CGS method:" << endl;
	#endif

	const double eps = 1e-12;
	int n_iter = 1;

	if ( size != b.getDim()) {
		cerr << "CGS: Dimension mismatch!" << endl;
	}

	Vector x(size);
	Vector r(b);
	Vector u(b);
	Vector p(b);
	Vector r0(b);
	Vector v(size);
	Vector q(size);
	Vector uq(size);
	Vector Auq(size);
	double rjr0;
	double rj1r0;
	double alpha;
	double beta;
	
	rjr0 = r0*r0;
	do {
		v = (*this) * p;
		alpha = rjr0/(v * r0);
		q.assignVec1PlusVec2MultByScalar(u, -alpha, v);
		uq.assignVec1PlusVec2MultByScalar(u, 1, q);
		x.addVectorMultByScalar(alpha, uq);
		Auq = (*this) * uq;
		r.addVectorMultByScalar(-alpha, Auq);
		rj1r0 = r*r0;
		beta = rj1r0/rjr0;
		u.assignVec1PlusVec2MultByScalar(r, beta, q);
		p.updateP(beta, beta, u, q, p);

		rjr0 = rj1r0;
		++n_iter;
	//	if (n_iter > size) {
	//		cerr << "The CGS method did not converge!" << endl;
	//		return x;
	//	}
	} while (sqrt( r * r) > eps);

	#ifndef NDEBUG
	cout << "The CGS method ended after " << n_iter << " iterations." << endl;
	#endif

	return x;
}

Vector SparseMatrix::matmul (const Vector &x, const vector<int> &innerpoints)
{
//	Vector result = Vector(innerpoints.size());
//	int c = 0;
//	int c2 = 0;
//	double val = 0.0;
//	double d = 0.0;
//	vector<int>::const_iterator iter = innerpoints.begin();
//	vector<int>::const_iterator iter2;
//	while (iter != innerpoints.end()) {
//		for (iter2 = innerpoints.begin(); iter2 != innerpoints.end(); ++iter2, ++c) {
//			val = A.getValue(*iter-1, *iter2-1);
//			d += val * x[c];
//		}
//		result.setEntry(c2, d);
//		c = 0;
//		d = 0;
//		c2++;
//		iter++;;
//	}
//	return result;
	int ninnerpoints = innerpoints.size();
	#ifndef NDEBUG
	if (x.getDim() != ninnerpoints)
		cerr << "Error: matmul(): Vector dimension and number of inner points do not match!" << endl;
	#endif

	Vector result = Vector(ninnerpoints);

	list<MatrixEntry*> *rowlist;
	list<MatrixEntry*>::iterator iter;
	double res = 0.0;
	int index = 0;
	double a = 0.0;

	vector<int>::const_iterator k;
	for (k = innerpoints.begin(); k != innerpoints.end(); ++k) {
		rowlist = &rows[*k - 1];
		iter = rowlist->begin();
		for (int ind = 0; ind < ninnerpoints; ++ind) {
			while ( (*iter)->getCol() < (innerpoints[ind]-1) && iter != rowlist->end() ) {
				iter++;
			}
			if ( (*iter)->getCol() == (innerpoints[ind] - 1) ) {
				a = (*iter)->getValue();
				res += a * x[ind];
			}
		}
		result.setEntry(index, res);
		res = 0.0;
		index++;
	}

	return result;
}


Vector SparseMatrix::conjugateGradientInnerPoints(const Vector &b, const vector<Vertex> &points)
{
	#ifndef NDEBUG
	cout << "Entering Conjugate Gradient Inner Points method:" << endl;
	#endif

	const double eps = 1e-12;
	int n_iter = 1;
	
	// Create a vector<int> containing the numbers of each inner point:
	vector<int> innerpoints;
	vector<Vertex>::const_iterator iter = points.begin();
	while (iter != points.end()) {
		if (iter->getLocation() == 0) {
			innerpoints.push_back(iter->getNumber());
		}
		iter++;
	}

	size_t ninnerpoints = innerpoints.size();
	Vector x(ninnerpoints);

	Vector r(ninnerpoints);
	Vector p(ninnerpoints);
	Vector Ap = Vector(ninnerpoints);
	
	vector<int>::iterator it = innerpoints.begin();
	for (int i = 0; i < (int)ninnerpoints; i++) {
		r.setEntry(i, b[*it- 1] );
		p.setEntry(i, b[*it- 1] );
		++it;
	}

	double rsold, rsnew;
	double alpha, beta;
	
	rsold = r*r;
	while (true) {
		Ap = matmul(p, innerpoints);
		alpha = rsold/(p * Ap);
		x.addVectorMultByScalar(alpha, p);
		r.addVectorMultByScalar(-alpha, Ap);
		rsnew = r*r;
		if ( sqrt(rsnew) < eps ) {
			#ifndef NDEBUG
			cout << "Conjugate Gradient method ended after " << n_iter << " iterations." << endl;
			#endif
			return x;
		}
		beta = rsnew/rsold;
		p.multByScalarAddVector(beta, r);
		rsold = rsnew;
		n_iter++;

		#ifndef NDEBUG
		if (n_iter > (int)ninnerpoints) {
			cerr << "Error: Conjugate Gradient method did not converge!" << endl;
			return x;
		}
		#endif
	}
	return x;
}

void SparseMatrix::addElementMatrix(Element &elem, Matrix3 &Ael)
{
	int p0, p1, p2;
	double val;
	p0 = elem.getPoint1().getNumber() - 1;
	p1 = elem.getPoint2().getNumber() - 1;
	p2 = elem.getPoint3().getNumber() - 1;

	val = Ael.get0();
	addEntry(p0, p0, val);

	val = Ael.get1();
	addEntry(p0, p1, val);

	val = Ael.get2();
	addEntry(p0, p2, val);

	val = Ael.get3();
	addEntry(p1, p0, val);

	val = Ael.get4();
	addEntry(p1, p1, val);

	val = Ael.get5();
	addEntry(p1, p2, val);

	val = Ael.get6();
	addEntry(p2, p0, val);

	val = Ael.get7();
	addEntry(p2, p1, val);

	val = Ael.get8();
	addEntry(p2, p2, val);
}


void SparseMatrix::addEdgeMatrix(Edge &edge, Matrix2 &M)
{
	int p0, p1;
	double val;
	p0 = edge.getPoint1().getNumber() - 1;
	p1 = edge.getPoint2().getNumber() - 1;

	val = M.get0();
	addEntry(p0, p0, val);

	val = M.get1();
	addEntry(p0, p1, val);

	val = M.get2();
	addEntry(p1, p0, val);

	val = M.get3();
	addEntry(p1, p1, val);
}
