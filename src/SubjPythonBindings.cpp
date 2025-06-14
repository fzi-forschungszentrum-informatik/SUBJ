#define STRINGIFY(s) STRFY(s)
#define STRFY(s) #s

#include <Eigen/Dense>
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>
#include <subj/BinomialOpinion.h>
#include <subj/Histogram.h>
#include <subj/MultinomialOpinion.h>
#include <subj/Operators.h>

namespace py = pybind11;

PYBIND11_MODULE(pysubj, m)
{
  m.doc() = R"pbdoc(The core module of pySUBJ, a Subjective Logic Library for Python)pbdoc";

  py::class_<subj::OpinionOwner>(m, "OpinionOwner")
    .def(py::init(), "Create an opinion owner.")
    .def("__repr__", [](const subj::OpinionOwner& pdf) {
      std::stringstream stream;
      stream << "<OpinionOwner>";
      return stream.str();
    });

  py::class_<subj::DirichletPDF>(m, "DirichletPDF")
    .def(py::init(), "Create a dirichlet pdf.")
    .def("updateEvidence",
         static_cast<void (subj::DirichletPDF::*)(const std::vector<double>&)>(
           &subj::DirichletPDF::updateEvidence),
         "Update the dirichlet pdf's evidence.")
    .def("updateEvidence",
         static_cast<void (subj::DirichletPDF::*)(const Eigen::VectorXd&)>(
           &subj::DirichletPDF::updateEvidence),
         "Update the dirichlet pdf's evidence.")
    .def("updateBaseRate",
         static_cast<void (subj::DirichletPDF::*)(const std::vector<double>&)>(
           &subj::DirichletPDF::updateBaseRate),
         "Update the dirichlet pdf's base rate.")
    .def("updateBaseRate",
         static_cast<void (subj::DirichletPDF::*)(const Eigen::VectorXd&)>(
           &subj::DirichletPDF::updateBaseRate),
         "Update the dirichlet pdf's base rate.")
    .def("evidence", &subj::DirichletPDF::evidence, "Return the dirichlet pdf's evidence.")
    .def("evidenceMat",
         &subj::DirichletPDF::evidenceMat,
         "Return the dirichlet pdf's evidence as numpy array.")
    .def("baseRate", &subj::DirichletPDF::baseRate, "Return the dirichlet pdf's base rate.")
    .def("baseRateMat",
         &subj::DirichletPDF::baseRate,
         "Return the dirichlet pdf's base rate as numpy array.")
    .def("strength", &subj::DirichletPDF::strength, "Return the dirichlet pdf's strength.")
    .def("strengthMat",
         &subj::DirichletPDF::strength,
         "Return the dirichlet pdf's strength as numpy array.")
    .def("density",
         static_cast<double (subj::DirichletPDF::*)(const std::vector<double>&) const>(
           &subj::DirichletPDF::density),
         "Return the dirichlet pdf's density at the given point.")
    .def("density",
         static_cast<double (subj::DirichletPDF::*)(const Eigen::VectorXd&) const>(
           &subj::DirichletPDF::density),
         "Return the dirichlet pdf's density at the given point.")
    .def("__repr__", [](const subj::DirichletPDF& pdf) {
      std::stringstream stream;
      stream << "<DirichletPDF: " << pdf << ">";
      return stream.str();
    });

  py::class_<subj::MultinomialOpinion>(m, "MultinomialOpinion")
    .def(py::init<const uint32_t>(), "Create a multinomial opinion with given dimension.")
    .def(py::init<const std::vector<double>&, const double&, const std::vector<double>&>())
    .def(py::init<const Eigen::VectorXd&, const double&, const Eigen::VectorXd&>())
    .def("update",
         static_cast<bool (subj::MultinomialOpinion::*)(
           const std::vector<double>&, const double&, const std::vector<double>&)>(
           &subj::MultinomialOpinion::update),
         "Update the opinion's belief, uncertainty and base rate.")
    .def("update",
         static_cast<bool (subj::MultinomialOpinion::*)(
           const Eigen::VectorXd&, const double&, const Eigen::VectorXd&)>(
           &subj::MultinomialOpinion::update),
         "Update the opinion's belief, uncertainty and base rate.")
    .def("updateBelief",
         static_cast<bool (subj::MultinomialOpinion::*)(const std::vector<double>&)>(
           &subj::MultinomialOpinion::updateBelief),
         "Update the opinion's belief.")
    .def("updateBelief",
         static_cast<bool (subj::MultinomialOpinion::*)(const Eigen::VectorXd&)>(
           &subj::MultinomialOpinion::updateBelief),
         "Update the opinion's belief.")
    .def("b",
         static_cast<bool (subj::MultinomialOpinion::*)(const std::vector<double>&)>(
           &subj::MultinomialOpinion::b),
         "Update the opinion's belief.")
    .def("b",
         static_cast<bool (subj::MultinomialOpinion::*)(const Eigen::VectorXd&)>(
           &subj::MultinomialOpinion::b),
         "Update the opinion's belief.")
    .def("belief", &subj::MultinomialOpinion::belief, "Return the opinion's belief.")
    .def("beliefMat",
         &subj::MultinomialOpinion::beliefMat,
         "Return the opinion's belief as numpy array.")
    .def("b",
         static_cast<std::vector<double> (subj::MultinomialOpinion::*)() const>(
           &subj::MultinomialOpinion::b),
         "Return the opinion's belief.")
    .def("bMat", &subj::MultinomialOpinion::bMat, "Return the opinion's belief as numpy array.")
    .def("updateUncertainty",
         &subj::MultinomialOpinion::updateUncertainty,
         "Update the opinion's uncertainty.")
    .def(
      "u",
      static_cast<bool (subj::MultinomialOpinion::*)(const double&)>(&subj::MultinomialOpinion::u),
      "Update the opinion's uncertainty.")
    .def("uncertainty",
         static_cast<double (subj::MultinomialOpinion::*)() const>(
           &subj::MultinomialOpinion::uncertainty),
         "Return the opinion's uncertainty.")
    .def("u",
         static_cast<double (subj::MultinomialOpinion::*)() const>(&subj::MultinomialOpinion::u),
         "Return the opinion's uncertainty.")
    .def("updateBaseRate",
         static_cast<bool (subj::MultinomialOpinion::*)(const std::vector<double>&)>(
           &subj::MultinomialOpinion::updateBaseRate),
         "Update the opinion's base rate.")
    .def("updateBaseRate",
         static_cast<bool (subj::MultinomialOpinion::*)(const Eigen::VectorXd&)>(
           &subj::MultinomialOpinion::updateBaseRate),
         "Update the opinion's base rate.")
    .def("a",
         static_cast<bool (subj::MultinomialOpinion::*)(const std::vector<double>&)>(
           &subj::MultinomialOpinion::a),
         "Update the opinion's base rate.")
    .def("a",
         static_cast<bool (subj::MultinomialOpinion::*)(const Eigen::VectorXd&)>(
           &subj::MultinomialOpinion::a),
         "Update the opinion's base rate.")
    .def("baseRate", &subj::MultinomialOpinion::baseRate, "Return the opinion's base rate.")
    .def("baseRateMat",
         &subj::MultinomialOpinion::baseRateMat,
         "Return the opinion's base rate as numpy array.")
    .def("a",
         static_cast<std::vector<double> (subj::MultinomialOpinion::*)() const>(
           &subj::MultinomialOpinion::a),
         "Return the opinion's base rate.")
    .def("aMat", &subj::MultinomialOpinion::aMat, "Return the opinion's base rate as numpy array.")
    .def("owner", &subj::MultinomialOpinion::owner, "Return the opinion's owner.")
    .def("updateOwner", &subj::MultinomialOpinion::updateOwner, "Update the opinion's owner.")
    .def("dirichletPdf",
         &subj::MultinomialOpinion::dirichletPdf,
         "Return the opinion's dirichlet pdf.")
    .def("dir", &subj::MultinomialOpinion::dir, "Return the opinion's dirichlet pdf.")
    .def("update",
         static_cast<void (subj::MultinomialOpinion::*)(subj::DirichletPDF&)>(
           &subj::MultinomialOpinion::update),
         "Update the opinion based on the given dirichlet pdf.")
    .def("projection", &subj::MultinomialOpinion::projection, "Return the opinion's projection.")
    .def("projectionMat",
         &subj::MultinomialOpinion::projectionMat,
         "Return the opinion's projection as numpy array.")
    .def("p", &subj::MultinomialOpinion::p, "Return the opinion's projection.")
    .def("pMat", &subj::MultinomialOpinion::pMat, "Return the opinion's projection as numpy array.")
    .def("variance", &subj::MultinomialOpinion::variance, "Return the opinion's variance.")
    .def("varianceMat",
         &subj::MultinomialOpinion::varianceMat,
         "Return the opinion's variance as numpy array.")
    .def("var", &subj::MultinomialOpinion::var, "Return the opinion's variance.")
    .def(
      "varMat", &subj::MultinomialOpinion::varMat, "Return the opinion's variance as numpy array.")
    .def("uncertaintyMaximum",
         &subj::MultinomialOpinion::uncertaintyMaximum,
         "Return the opinion's uncertainty maximum.")
    .def("uMax", &subj::MultinomialOpinion::uMax, "Return the opinion's uncertainty maximum.")
    .def("dim", &subj::MultinomialOpinion::dim, "Return the opinion's dimension.")
    .def("__repr__", [](const subj::MultinomialOpinion& op) {
      std::stringstream stream;
      stream << "<MultinomialOpinion: " << op << ">";
      return stream.str();
    });

  py::class_<subj::BinomialOpinion, subj::MultinomialOpinion>(m, "BinomialOpinion")
    .def(py::init(), "Create a binomial opinion.")
    .def(py::init<const double&, const double&, const double&, const double&>(),
         "Create a binomial opinion with given belief, disbelief, uncertainty and base rate.")
    .def("update",
         &subj::BinomialOpinion::update,
         "Update the opinion's belief, disbelief, uncertainty and base rate.")
    .def("updateBelief", &subj::BinomialOpinion::updateBelief, "Update the opinion's belief.")
    .def("b",
         static_cast<bool (subj::BinomialOpinion::*)(double)>(&subj::BinomialOpinion::b),
         "Update the opinion's belief.")
    .def(
      "updateDisbelief", &subj::BinomialOpinion::updateDisbelief, "Update the opinion's disbelief.")
    .def("d",
         static_cast<bool (subj::BinomialOpinion::*)(double)>(&subj::BinomialOpinion::d),
         "Update the opinion's disbelief.")
    .def(
      "updateBaseRate", &subj::BinomialOpinion::updateBaseRate, "Update the opinion's base rate.")
    .def("a",
         static_cast<bool (subj::BinomialOpinion::*)(double)>(&subj::BinomialOpinion::a),
         "Update the opinion's base rate.")
    .def("belief", &subj::BinomialOpinion::belief, "Return the opinion's belief.")
    .def("b",
         static_cast<double (subj::BinomialOpinion::*)() const>(&subj::BinomialOpinion::b),
         "Return the opinion's belief.")
    .def("disbelief", &subj::BinomialOpinion::disbelief, "Return the opinion's disbelief.")
    .def("d",
         static_cast<double (subj::BinomialOpinion::*)() const>(&subj::BinomialOpinion::d),
         "Return the opinion's disbelief.")
    .def("baseRate", &subj::BinomialOpinion::baseRate, "Return the opinion's base rate.")
    .def("a",
         static_cast<double (subj::BinomialOpinion::*)() const>(&subj::BinomialOpinion::a),
         "Return the opinion's base rate.")
    .def("projection", &subj::BinomialOpinion::projection, "Return the opinion's projection.")
    .def("p", &subj::BinomialOpinion::p, "Return the opinion's projection.")
    .def("variance", &subj::BinomialOpinion::variance, "Return the opinion's variance.")
    .def("var", &subj::BinomialOpinion::var, "Return the opinion's var.")
    .def("__repr__", [](const subj::BinomialOpinion& op) {
      std::stringstream stream;
      stream << "<BinomialOpinion: " << op << ">";
      return stream.str();
    });

  py::class_<subj::Histogram>(m, "Histogram")
    .def(py::init(), "Create a Histogram.")
    //     .def(py::init<size_t>(), "Create a histogram with given number of equally sized bins.")
    .def(py::init<size_t, double, double>(),
         "Create a histogram with given number of equally sized bins between given minimum and "
         "maximum value.")
    .def(py::init<size_t, const Eigen::VectorXd&>(),
         "Create a histogram with given number of equally sized bins between minimum and "
         "maximum value of given data and fill histogram with this data.")
    .def(py::init<size_t, const Eigen::VectorXd&, double, double>(),
         "Create a histogram with given number of equally sized bins between given minimum and "
         "maximum value and fill histogram with given data.")
    .def("insert",
         static_cast<void (subj::Histogram::*)(double)>(&subj::Histogram::insert),
         "Insert the given value into the histogram.")
    .def("insertIntoBin",
         &subj::Histogram::insertIntoBin,
         "Insert into a given bin (e.g. increase the amount of values in the given bin by 1).")
    .def("insert",
         static_cast<void (subj::Histogram::*)(const Eigen::VectorXd&)>(&subj::Histogram::insert),
         "Insert the given data into the histogram.")
    .def("histogram", &subj::Histogram::histogram, "Return the histogram as numpy array.")
    .def("intervals", &subj::Histogram::intervals, "Return the intervals of the histogram.")
    .def("normalizedHistogram",
         &subj::Histogram::normalizedHistogram,
         "Return the histogram in normalized form (i.e. all values sum to 1). If no data is in the "
         "histogram, return an all-zero histogram.")
    .def("dataSize", &subj::Histogram::dataSize, "Return the amount of data in the histogram.")
    .def(
      "binIndex",
      &subj::Histogram::binIndex,
      "Returns the index of the given value for this histogram, without altering the histogram.");

  m.def("projectedDistance",
        subj::projectedDistance,
        "Calculates the projected distance of two given opinions.");
  m.def("pd", subj::pd, "Calculates the projected distance of two given opinions.");
  m.def("conjunctiveCertainty",
        subj::conjunctiveCertainty,
        "Calculates the conjunctive certainty of two given opinions.");
  m.def("cc", subj::cc, "Calculates the conjunctive certainty of two given opinions.");
  m.def("degreeOfConflict",
        subj::degreeOfConflict,
        "Calculates the degree of conflict of two given opinions.");
  m.def("doc", subj::doc, "Calculates the degree of conflict of two given opinions.");
  m.def("averagingBeliefFusion",
        subj::averagingBeliefFusion,
        "Calculates the averaging belief fusion of multiple given opinions.");
  m.def("abf", subj::abf, "Calculates the averaging belief fusion of multiple given opinions.");
  m.def("aleatoryCumulativeBeliefFusion",
        static_cast<subj::MultinomialOpinion (*)(const std::vector<subj::MultinomialOpinion>&)>(
          &subj::aleatoryCumulativeBeliefFusion),
        "Calculates the aleatory cumulative belief fusion of multiple given opinions.");
  m.def("aleatoryCumulativeBeliefFusion",
        static_cast<subj::MultinomialOpinion (*)(const subj::MultinomialOpinion&,
                                                 const subj::MultinomialOpinion&)>(
          &subj::aleatoryCumulativeBeliefFusion),
        "Calculates the aleatory cumulative belief fusion of two given opinions.");
  m.def("cbf",
        static_cast<subj::MultinomialOpinion (*)(const std::vector<subj::MultinomialOpinion>&)>(
          &subj::cbf),
        "Calculates the aleatory cumulative belief fusion of multiple given opinions.");
  m.def("cbf",
        static_cast<subj::MultinomialOpinion (*)(const subj::MultinomialOpinion&,
                                                 const subj::MultinomialOpinion&)>(&subj::cbf),
        "Calculates the aleatory cumulative belief fusion of two given opinions.");
  m.def("cumulativeUnfusion",
        subj::cumulativeUnfusion,
        "Calculates the cumulative unfusion of a given opinion from a fused opinion with given "
        "base rate.");
  m.def("trustDiscounting",
        subj::trustDiscounting,
        "Calculates the trust discounted opinion of a given opinion and a discount probability.");
  m.def("td",
        subj::td,
        "Calculates the trust discounted opinion of a given opinion and a discount probability.");
  m.def("normalMultiplication",
        subj::normalMultiplication,
        "Calculates the normal multiplication of two given opinions.");
  m.def("deduction",
        subj::deduction,
        "Calculates the deduction of a given opinion and a list of conditional opinions.");

#ifdef VERSION_INFO
  m.attr("__version__") = STRINGIFY(VERSION_INFO);
#endif
}
